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
	param->number_must_eat = 0;
	param->died = 0;
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
	int i;

	i = 1;
	while (i <= param->number_of_philo)
	{
		pthread_mutex_init(&(param->fork[i]), NULL);
		i++;
	}
	// pthread_mutex_init(&param->mutex, NULL);
}

void	*ft_eat(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (param.died == 0 && p->left_fork != 0 && p->right_fork != 0)
	{
		p->col_eat += 1;
		printf("%lld    %d    is eating | col_eat: %d\n", check_time() - param.time_start, p->num_philo, p->col_eat);
		p->last_eat = check_time();
		user_sleep(param.time_to_eat);
	}
	pthread_mutex_unlock(&param.fork[p->left_fork]);
	pthread_mutex_unlock(&param.fork[p->right_fork]);
	return (NULL);
}

void	*take_forks(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&param.fork[p->left_fork]);
	if (param.died == 0 && p->left_fork != 0)
		printf("%lld    %d    has taken a left fork\n", check_time() - param.time_start, p->num_philo);
	pthread_mutex_lock(&param.fork[p->right_fork]);
	if (param.died == 0 && p->right_fork != 0)
		printf("%lld    %d    has taken a right fork\n", check_time() - param.time_start, p->num_philo);
	return (NULL);
}

void	*ft_sleep(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (param.died == 0 && p->col_eat != 0)
	{
		printf("%lld    %d    is sleeping\n", check_time() - param.time_start, p->num_philo);
		user_sleep(param.time_to_sleep);
	}
	return (NULL);
}

void	*ft_thinking(void *philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (param.died == 0 && p->col_eat != 0)
		printf("%lld    %d    is thinking\n", check_time() - param.time_start, p->num_philo);
	return (NULL);
}

void	*life(void	*philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	// if (p->num_philo % 2 == 0)
	// 	usleep(500);
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		if (p->col_eat == param.must_eat && param.number_of_philo > 1)
			break ;
		ft_sleep(philo);
		ft_thinking(philo);
		if ((p->left_fork == 0 || p->right_fork == 0 ) || param.died != 0)
		{
			if (p->left_fork == 0 || p->right_fork == 0)
			{
				while (param.died == 0)
					usleep (1);
			}
			break ;
		}
	}
	return (NULL);
}

void	*thread_death(void *param)
{
	t_param *p;

	p = (t_param *)param;
	int i;

	i = 1;
	while (1)
	{
		i = 1;
		while (i <= p->number_of_philo)
		{
			if (check_time() - p->philo[i].last_eat > p->time_to_die)
			{
				p->died = p->philo[i].num_philo;
				printf("%lld    %d    died\n", check_time() - p->time_start, p->died);
				return (NULL);
			}
			i++;
		}
		usleep (10);
	}
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
		if (param.philo[i].num_philo % 2 == 0)
			usleep(200);
		pthread_create(&param.tread[i], NULL, life, &param.philo[i]);
	}
	pthread_create(&param.die, NULL, thread_death, &param);


	for (int i = 1; i <= param.number_of_philo; i++)
	{
		pthread_join(param.tread[i], NULL);
	}

	
	
    // printf("number_of_philos: %d\n", param.number_of_philo);
    // printf("time_to_die: %d\n", param.time_to_die);
	// printf("time_to_eat: %d\n", param.time_to_eat);
	// printf("time_to_sleep: %d\n", param.time_to_sleep);
	// printf("must_eat: %d\n", param.must_eat);
	// printf("time_start: %lld\n", param.time_start);
	// for (int i = 1; i <= param.number_of_philo; i++)
	// 	printf("i: %d num_philo: %d left: %d right: %d\n", i, param.philo[i].num_philo, param.philo[i].left_fork, param.philo[i]. right_fork);
}