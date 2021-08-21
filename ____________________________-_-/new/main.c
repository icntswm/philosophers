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
		param->philo[i].left_fork = i;
		if (i == param->number_of_philo)
			param->philo[i].right_fork = 1;
		else
			param->philo[i].right_fork = i + 1;
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
	pthread_mutex_init(&param->mutex, NULL);
}

void	*ft_eat(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	p->eating = 1;
	param.check += 1;
	printf("%lld    %d    is eating\n", check_time() - param.time_start, p->num_philo);
	user_sleep(param.time_to_sleep);
	return (NULL);
}

void	*take_forks(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&param.fork[p->left_fork]);
	printf("%lld    %d    has taken a left fork\n", check_time() - param.time_start, p->num_philo);
	pthread_mutex_lock(&param.fork[p->right_fork]);
	// printf("%lld    %d    has taken a left fork\n", check_time() - param.time_start, p->num_philo);
	// pthread_mutex_lock(&param.fork[p->right_fork]);
	printf("%lld    %d    has taken a right fork\n", check_time() - param.time_start, p->num_philo);
	ft_eat(philo);
	// pthread_mutex_unlock(&param.fork[p->left_fork]);
	// pthread_mutex_unlock(&param.fork[p->right_fork]);
	return (NULL);
}

void	*life(void	*philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	param.check = 0;
	while (1)
	{
		take_forks(philo);
	}
		// printf("%lld    %d    has taken a fork\n", check_time() - param.time_start, p->num_philo);
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
		printf("i: %d num_philo: %d left: %d right: %d\n", i, param.philo[i].num_philo, param.philo[i].left_fork, param.philo[i]. right_fork);
}