#include "philo.h"

long long check_time()
{
	struct timeval tv;
	long long milisec;

	milisec = 0;
	gettimeofday(&tv, NULL);
	milisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milisec);
}

void    parser(char **argv, t_strc *strc)
{
	if (argv[5] != NULL)
        strc->must_eat = ft_atoi(argv[5]);
    else
        strc->must_eat = 0;
	strc->time_to_sleep = ft_atoi(argv[4]);
	strc->time_to_eat = ft_atoi(argv[3]);
	strc->time_to_die = ft_atoi(argv[2]);
	strc->number_of_philo = ft_atoi(argv[1]);
	strc->time_start = check_time();
	strc->number_of_forks = strc->number_of_philo;
	strc->philos = (t_philo *)malloc(sizeof(t_philo) * strc->number_of_philo);
	strc->threads = (pthread_t *)malloc(sizeof(pthread_t) * strc->number_of_philo);
	strc->check = 0;
}

void	init_philos(t_strc	*strc)
{
	int i;

	for (i = 1; i <= strc->number_of_philo; i++)
	{
		strc->philos[i].num_philo = i;
		strc->philos[i].col_forks = 0;
		strc->philos[i].eating = 0;
	}
}

void	init_mutex(t_strc *strc)
{
	pthread_mutex_init(&strc->dead, NULL);
	pthread_mutex_init(&strc->forks, NULL);
	pthread_mutex_init(&strc->forks1, NULL);
}

void	user_sleep(long long time)
{
	long long	save_time;
	
	save_time = check_time();
	while (1)
	{
		if (check_time() == (save_time + time))
			break;
	}
}

void	*ft_eat(void	*philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	if (p->col_forks )
	p->eating = 1;
	p->col_forks = 0;
	printf("%lld    %d is eating\n", check_time() - strc.time_start, p->num_philo);
	strc.check += 1;
	user_sleep(strc.time_to_eat);
	printf("%lld    %d is sleeping\n", check_time() - strc.time_start, p->num_philo);
	strc.number_of_forks += 2;
	return (NULL);
}

void	*ft_sleep(void	*philo)
{
	t_philo *p;

	p = (t_philo *)philo;
	// printf("%lld    %d is sleeping\n", check_time() - strc.time_start, p->num_philo);
	p->eating = 0;
	user_sleep(strc.time_to_sleep);
	printf("%lld    %d is thinking\n", check_time() - strc.time_start, p->num_philo);
	// while (strc.check != strc.number_of_philo && (check_time() - strc.time_start < strc.time_to_die))
	// {
	// 	user_sleep(1);
	// 	if (strc.check == strc.number_of_philo)
	// 	{
	// 		strc.check = 0;
	// 		break ;
	// 	}
	// }
	return (NULL);
}

void	*take_fork(void	*philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&strc.forks);
	while (1)
	{
		while (ph->col_forks != 2 && strc.number_of_forks > 0)
		{
			strc.number_of_forks--;
			ph->col_forks++;
			printf("%lld    %d has taken a fork\n", check_time() - strc.time_start, ph->num_philo);
		}
		if (ph->col_forks == 2)
			break ;
	}
	pthread_mutex_unlock(&strc.forks);

}

void	*wwwww(void	*philo)
{
	t_philo *p;
	int s;

	s = 0;
	p = (t_philo *)philo;
	while (1)
	{
		if (p->eating == 0)
			take_fork((void *)philo);
		if (p->col_forks == 2)
			ft_eat((void *)philo);
		if (p->eating == 1)
			ft_sleep((void *)philo);
		// if (strc.check == strc.number_of_philo && p->eating == 1)
		// {
		// 	p->eating = 0;
		// 	s++;
		// 	if (s = strc.number_of_philo)
		// 		s = 0;
		// }
	}
	
}

int main(int argc, char **argv)
{
    error(argc);
    parser(argv, &strc);

	init_philos(&strc);
	init_mutex(&strc);
	for(int i = 1; i <= strc.number_of_philo; i++)
		pthread_create(&strc.threads[i], NULL, wwwww, &strc.philos[i]);
	for(int i = 1; i <= strc.number_of_philo; i++)
		pthread_join(strc.threads[i], NULL);
	printf("time_start: %lld\n", strc.time_start);
    printf("number_of_philos: %d\n", strc.number_of_philo);
    printf("time_to_die: %d\n", strc.time_to_die);
	printf("time_to_eat: %d\n", strc.time_to_eat);
	printf("time_to_sleep: %d\n", strc.time_to_sleep);
	printf("must_eat: %d\n", strc.must_eat);

	for(int i = 1; i <= strc.number_of_philo; i++)
	{
		printf("i:%d | philo: %d", i, strc.philos[i].num_philo);
		printf(" col_forks: %d eating: %d",  strc.philos[i].col_forks, strc.philos[i].eating);
		printf(" number_of_forks: %d\n", strc.number_of_forks);
	}
}