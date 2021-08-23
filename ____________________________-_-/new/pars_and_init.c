#include "philo_new.h"

void	parser(t_param *param, char **argv)
{
	param->number_of_philo = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->must_eat = ft_atoi(argv[5]);
	else
		param->must_eat = 0;
	param->time_start = check_time();
	param->time_end = 0;
	param->check_eat_for_thrdeath = 0;
	param->died = 0;
	param->tread = (pthread_t *)malloc(sizeof(pthread_t)
			* param->number_of_philo);
	param->philo = (t_philo *)malloc(sizeof(t_philo) * param->number_of_philo);
	param->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* param->number_of_philo);
}

void	philo_init(t_param *param)
{
	int	i;

	i = 1;
	while (i <= param->number_of_philo)
	{
		param->philo[i].num_philo = i;
		param->philo[i].left_fork = i;
		if (i == param->number_of_philo && param->number_of_philo > 1)
			param->philo[i].right_fork = 1;
		else if (i == param->number_of_philo && param->number_of_philo == 1)
			param->philo[i].right_fork = 0;
		else
			param->philo[i].right_fork = i + 1;
		param->philo[i].last_eat = check_time();
		param->philo[i].col_eat = 0;
		i++;
	}
}

void	mutex_init(t_param *param)
{
	int	i;

	i = 1;
	while (i <= param->number_of_philo)
	{
		pthread_mutex_init(&(param->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&param->mutex, NULL);
}
