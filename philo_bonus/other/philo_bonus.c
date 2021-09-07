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

void	*ft_check_death(void	*philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		sem_wait(ph->mutex);
		if (g_param.must_eat != 0 && ph->col_eat == g_param.must_eat)
			break ;
		if (check_time() - ph->last_eat > g_param.time_to_die)
		{
			sem_wait(g_param.mut);
			printf("%lld   ", check_time() - g_param.time_start);
			printf("%d   died\n", ph->num_philo);
			sem_post(g_param.kill);
			break ;
		}
		sem_post(ph->mutex);
		if (g_param.num_of_philo > 0 && g_param.num_of_philo <= 70)
			usleep(50);
		else if (g_param.num_of_philo > 70 && g_param.num_of_philo <= 130)
			usleep(500);
		else if (g_param.num_of_philo > 130 && g_param.num_of_philo <= 200)
			usleep(5000);
	}
	return (NULL);
}

void	take_forks(t_philo *ph)
{
	sem_wait(g_param.forks);
	sem_wait(g_param.mut);
	printf("%lld   ", check_time() - g_param.time_start);
	printf("%d   has taken a fork\n", ph->num_philo);
	sem_post(g_param.mut);
	sem_wait(g_param.forks);
	sem_wait(g_param.mut);
	printf("%lld   ", check_time() - g_param.time_start);
	printf("%d   has taken a fork\n", ph->num_philo);
	sem_post(g_param.mut);
}

void	ft_thinking(t_philo *ph)
{
	sem_wait(g_param.mut);
	printf("%lld   ", check_time() - g_param.time_start);
	printf("%d   is thinking\n", ph->num_philo);
	sem_post(g_param.mut);
}

void	ft_sleeping(t_philo *ph)
{
	sem_wait(g_param.mut);
	printf("%lld   ", check_time() - g_param.time_start);
	printf("%d   is sleeping\n", ph->num_philo);
	sem_post(g_param.mut);
	usleep(g_param.time_to_sleep);
}

void	ft_eat(t_philo *ph)
{
	sem_wait(ph->mutex);
	ph->col_eat++;
	ph->last_eat = check_time();
	sem_wait(g_param.mut);
	printf("%lld   ", check_time() - g_param.time_start);
	printf("%d   is eating\n", ph->num_philo);
	sem_post(g_param.mut);
	usleep(g_param.time_to_eat);
	sem_post(ph->mutex);
	sem_post(g_param.forks);
	sem_post(g_param.forks);
}

void	life(t_philo *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->last_eat = check_time();
	pthread_create(&ph->thread, NULL, &ft_check_death, ph);
	while (1)
	{
		take_forks(ph);
		ft_eat(ph);
		if (ph->col_eat == g_param.must_eat)
			break ;
		ft_sleeping(ph);
		ft_thinking(ph);
	}
	pthread_join(ph->thread, NULL);
	exit (0);
}

void	*ft_check_par_death(void	*g_par)
{
	int	i;

	i = 0;
	sem_wait(g_param.kill);
	while (i < g_param.num_of_philo)
	{
		kill(g_param.ph[i].die, 1);
		i++;
	}
	return (NULL);
}

void	child_proc(void)
{
	int	i;

	i = 0;
	philo_init();
	while (i < g_param.num_of_philo)
	{
		g_param.ph[i].die = fork();
		if (g_param.ph[i].die == 0)
			life(&g_param.ph[i]);
		i++;
	}
	pthread_create(&g_param.check_die, NULL, &ft_check_par_death, &g_param);
	i = 0;
	while (i < g_param.num_of_philo)
	{
		waitpid(g_param.ph[i].die, NULL, 0);
		i++;
		if (i == g_param.num_of_philo)
			sem_post(g_param.kill);
	}
	pthread_join(g_param.check_die, NULL);
}

void	ft_free(void)
{
	int	i;

	i = 0;
	if (g_param.ph)
	{
		while (i < g_param.num_of_philo)
		{
			if (sem_unlink(g_param.ph[i].name_s) == -1)
				printf("lol\n");
			if (sem_close(g_param.ph[i].mutex) == -1)
				printf("kek\n");
			free(g_param.ph[i].name_s);
			g_param.ph[i].name_s = NULL;
			i++;
		}
		free(g_param.ph);
	}
	sem_unlink("sem_forks");
	sem_close(g_param.forks);
	sem_unlink("sem_mut");
	sem_close(g_param.mut);
	sem_unlink("sem_kill");
	sem_close(g_param.kill);
}

int	main(int argc, char **argv)
{
	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	init_sem_forks();
	child_proc();
	ft_free();
	return (0);
}
