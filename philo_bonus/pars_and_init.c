#include "philo_bonus.h"

void	parser(t_param *g_param, char **argv)
{
	g_param->num_of_philo = ft_atoi(argv[1]);
	g_param->time_to_die = ft_atoi(argv[2]);
	g_param->time_to_eat = ft_atoi(argv[3]) * 1000;
	g_param->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
		g_param->must_eat = ft_atoi(argv[5]);
	else
		g_param->must_eat = 0;
	g_param->time_start = check_time();
}

void	init_sem_forks(void)
{
	int	val;

	val = g_param.num_of_philo;
	sem_unlink("sem_forks");
	g_param.forks = sem_open("sem_forks", O_CREAT, 0777, val);
	sem_unlink("sem_mut");
	g_param.mut = sem_open("sem_mut", O_CREAT, 0777, 1);
	sem_unlink("sem_kill");
	g_param.kill = sem_open("sem_kill", O_CREAT, 0777, 0);
}

char	*ft_sem_name(t_philo *ph)
{
	char	*num;
	char	*new;
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	name = "sem_mutex";
	num = ft_itoa(ph->num_philo);
	new = (char *)malloc(sizeof(char) * (ft_strlen(name) + ft_strlen(num) + 1));
	while (name[i])
		new[j++] = name[i++];
	i = 0;
	while (num[i])
		new[j++] = num[i++];
	free(num);
	new[j] = '\0';
	return (new);
}

void	philo_init(void)
{
	int	i;
	int	num;

	i = 0;
	num = g_param.num_of_philo;
	g_param.ph = (t_philo *)malloc(sizeof(t_philo) * num);
	while (i < g_param.num_of_philo)
	{
		g_param.ph[i].num_philo = i + 1;
		g_param.ph[i].col_eat = 0;
		g_param.ph[i].name_s = ft_sem_name(&g_param.ph[i]);
		sem_unlink(g_param.ph[i].name_s);
		g_param.ph[i].mutex = sem_open(g_param.ph[i].name_s, O_CREAT, 0777, 1);
		i++;
	}
}
