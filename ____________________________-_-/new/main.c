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
	param->tread = (pthread_t *)malloc(sizeof(pthread_t) * param->number_of_philo);
	param->philo = (t_philo *)malloc(sizeof(t_philo) * param->number_of_philo);
	param->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param->number_of_philo);
}

void	philo_init(t_param *param)
{
	int i;

	i = 1;
	while (i <= param->number_of_philo)
	{
		param->philo[i].num_philo = i;
		param->philo[i].left_fork = 0;
		param->philo[i].right_fork = 0;
		param->philo[i].eating = 0;
		i++;
	}
}

void	mutex_init(t_param *param)
{
	int i;

	i = 1;
	while (i <= param->number_of_philo)
	{
		pthread_mutex_init(&(param->fork[i]), NULL);
		i++;
	}
}

void	*life(void	*philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	printf("num: %d\n", p->num_philo);
	return (NULL);
}

int main(int argc, char **argv)
{
	error(argc);
	parser(&param, argv);
	philo_init(&param);
	mutex_init(&param);

	for (int i = 1; i <= param.number_of_philo; i++)
	{
		pthread_create(&param.tread[i], NULL, life, &param.philo[i]);
	}
	for (int i = 1; i <= param.number_of_philo; i++)
	{
		pthread_join(param.tread[i], NULL);
	}
	
	
    printf("number_of_philos: %d\n", param.number_of_philo);
    printf("time_to_die: %d\n", param.time_to_die);
	printf("time_to_eat: %d\n", param.time_to_eat);
	printf("time_to_sleep: %d\n", param.time_to_sleep);
	printf("must_eat: %d\n", param.must_eat);
	printf("time_start: %lld\n", param.time_start);
	for (int i = 1; i <= param.number_of_philo; i++)
		printf("i: %d num_philo: %d\n", i, param.philo[i].num_philo);
}