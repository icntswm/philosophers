#include "philo.h"

void	parser(t_param *g_param, char **argv)
{
	g_param->number_of_philo = ft_atoi(argv[1]);
	g_param->time_to_die = ft_atoi(argv[2]);
	g_param->time_to_eat = ft_atoi(argv[3]);
	g_param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_param->must_eat = ft_atoi(argv[5]);
	else
		g_param->must_eat = 0;
	g_param->time_start = check_time();
	g_param->time_end = 0;
	g_param->check_eat_for_thrdeath = 0;
	g_param->died = 0;
	g_param->philo = (t_philo *)malloc(sizeof(t_philo)
			* g_param->number_of_philo);
	g_param->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* g_param->number_of_philo);
}

void	philo_init(t_param *g_param)
{
	int	i;

	i = 0;
	while (i < g_param->number_of_philo)
	{
		g_param->philo[i].num_philo = i + 1;
		g_param->philo[i].left_fork = i;
		if (i == (g_param->number_of_philo - 1) && g_param->number_of_philo > 1)
			g_param->philo[i].right_fork = 0;
		else if (i == (g_param->number_of_philo - 1)
			&& g_param->number_of_philo == 1)
			g_param->philo[i].right_fork = -1;
		else
			g_param->philo[i].right_fork = i + 1;
		g_param->philo[i].last_eat = check_time();
		g_param->philo[i].col_eat = 0;
		i++;
	}
}

void	mutex_init(t_param *g_param)
{
	int	i;

	i = 0;
	while (i < g_param->number_of_philo)
	{
		pthread_mutex_init(&(g_param->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&g_param->mutex, NULL);
	pthread_mutex_init(&g_param->eat_death, NULL);
}
