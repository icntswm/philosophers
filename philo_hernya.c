#include "philo.h"

// void	*ft_sleep(void	*thread_fphil)
// {
// 	t_fphil *p;

// 	p = (t_fphil *)thread_fphil;
// 	printf("%-lld    %d is sleeping\n", check_time() - param.time_start, p->num_philo);
// 	user_sleep(param.time_to_sleep);
// 	// user_sleep(slp);
// 	return (NULL);
// }

// void	*ft_thinking(void	*thread_fphil)
// {
// 	t_fphil *p;
// 	long long check;
// 	p = (t_fphil *)thread_fphil;
// 	printf("%-lld    %d is thinking\n", check_time() - param.time_start, p->num_philo);
// 	// check = check_time();
// 	user_sleep(200);
// 	return (NULL);
// }

// void	*ft_eat(void	*thread_fphil)
// {
// 	t_fphil *p;

// 	p = (t_fphil *)thread_fphil;
// 	printf("%-lld    %d is eating\n", check_time() - param.time_start, p->num_philo);
// 	user_sleep(param.time_to_eat);
// 	p->col_fork = 0;
// 	// param.number_of_forks = param.number_of_forks + 2;
// 	return (NULL);
// }

// void	*taking_forks(void	*thread_fphil)
// {
// 	t_fphil *p;

// 	p = (t_fphil *)thread_fphil;
// 	while (1)
// 	{
// 		while (param.number_of_forks > 0)
// 		{
// 			p->col_fork++;
// 			param.number_of_forks--;
// 			printf("%-lld    %d has taken a fork | ost: %d\n", check_time() - param.time_start, p->num_philo, param.number_of_forks);
// 			if (p->col_fork == 2)
// 			{
// 				ft_eat(&(*thread_fphil));
// 				param.number_of_forks = param.number_of_forks + 2;
// 				pthread_mutex_unlock(&mutex);
// 				ft_sleep(&(*thread_fphil));
// 				ft_thinking(&(*thread_fphil));
// 			}
// 		}
// 		pthread_mutex_lock(&mutex);
// 	}
// 	return (NULL);
// }

t_glob	glob;

long long check_time()
{
	struct timeval tv;
	long long milisec;

	milisec = 0;
	gettimeofday(&tv, NULL);
	milisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milisec);
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

void	parser(char **argv, t_glob	*glob)
{
	if (argv[1] != NULL)
		glob->number_of_philos = ft_atoi(argv[1]);
	if (argv[2] != NULL)
		glob->time_to_die = ft_atoi(argv[2]);
	if (argv[3] != NULL)
		glob->time_to_eat = ft_atoi(argv[3]);
	if (argv[4] != NULL)
		glob->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		glob->max_eat = ft_atoi(argv[5]);
	else
		glob->max_eat = 0;
	glob->time_start = check_time();
	glob->check_eating = 0;
}

void	*ft_sleep(void	*param)
{
	t_philo *p;

	p = (t_philo *)param;
	// printf("%lld   %d is sleeping\n", check_time() - glob.time_start, p->num_philo);
	user_sleep(glob.time_to_sleep);
	// printf("%lld   %d is thinking\n", check_time() - glob.time_start, p->num_philo);
	return (NULL);
}

void	*ft_eat(void	*param)
{
	t_philo *p;

	p = (t_philo *)param;
	p->poel = 1;
	p->col_forks = 0;
	printf("%lld   %d is eating\n", check_time() - glob.time_start, p->num_philo);
	user_sleep(glob.time_to_eat);
	printf("%lld   %d is sleeping\n", check_time() - glob.time_start, p->num_philo);
	glob.number_of_philos += 2;
	return (NULL);
}

void	*taking_forks(void	*param)
{
	t_philo *p;

	p = (t_philo *)param;
	while (1)
	{
		// if (glob.number_of_philos == 0)
		// 	pthread_mutex_lock(&glob.col_fork);
		while (p->col_forks != 2 && glob.number_of_philos > 0 && p->poel == 0)
		{
			if (glob.number_of_philos == 0)
				pthread_mutex_lock(&glob.col_fork);
			p->col_forks++;
			glob.number_of_philos--;
			printf("%lld   %d has taken a fork | col_forks: %d | ost: %d\n", check_time() - glob.time_start, p->num_philo, p->col_forks, glob.number_of_philos);
			if (p->col_forks == 2)
			{
				ft_eat(&(*param));
				pthread_mutex_unlock(&glob.col_fork);
				ft_sleep(&(*param));
				break ;
			}
		}
	}
	return (NULL);
}
int main(int argc, char **argv)
{
	
	pthread_t	*threads;
	t_philo		*param;

	error(argc);
	parser(argv, &glob);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * glob.number_of_philos);
	printf("number_of_philosophers: %d\n", glob.number_of_philos);
	printf("time_to_die: %d\n",  glob.time_to_die);
	printf("time_to_eat: %d\n",   glob.time_to_eat);
	printf("time_to_sleep: %d\n",   glob.time_to_sleep);
	printf("max_eat: %d\n",   glob.max_eat);
	printf("check_eating: %d\n\n",   glob.check_eating);
	// glob.col_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * glob.number_of_philos);
	param = (t_philo *)malloc(sizeof(t_philo) * glob.number_of_philos);
	for(int i = 1; i <= glob.number_of_philos; i++)
	{
		param[i].num_philo = i;
		param[i].poel = 0;
		param[i].col_forks = 0;
		// pthread_mutex_init(&(glob.col_fork[i]), NULL);
	}
	pthread_mutex_init(&glob.col_fork, NULL);
	for(int i = 1; i <= glob.number_of_philos; i++)
		printf("i: %d, num_phil: %d, col_forks: %d, poel: %d\n", i, param[i].num_philo, param[i].col_forks, param[i].poel);
	for (int q = 1; q <= glob.number_of_philos; q++)
		pthread_create(&(threads[q]), NULL, taking_forks, &param[q]);
	for (int q = 1; q <= glob.number_of_philos; q++)
		pthread_join(threads[q], NULL);
	printf("\n");
	for(int i = 1; i <= glob.number_of_philos; i++)
		printf("i: %d, num_phil: %d, col_forks: %d, poel: %d\n", i, param[i].num_philo, param[i].col_forks, param[i].poel);
	






	// threads = (pthread_t *)malloc(sizeof(pthread_t) * param->number_of_philos);
	// printf("kek\n");
	// param = (t_phil *)malloc(sizeof(t_phil) * param->number_of_philos);
	// param->col_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param->number_of_philos);
	// printf("kek\n");
	// for(int i = 1; i <= param->number_of_philos; i++)
	// {
	// 	// parser(argv, &(param));
	// 	param[i].number_of_philos = ft_atoi(argv[i]);
	// 	param[i].num_philo = i;
	// }
	// for(int j = 1; j <= param->number_of_philos; j++)
	// 	printf("%d\n", param[j].num_philo);
	// pthread_t	*threads;
	// t_fphil		*thread_fphil;
	// pthread_mutex_init(&mutex, NULL);

	// threads = (pthread_t *)malloc(sizeof(pthread_t) * param.number_of_philos);
	// thread_fphil = (t_fphil *)malloc(sizeof(t_fphil) * param.number_of_philos);
	// for(int i = 1; i <= param.number_of_philos; i++)
	// {
	// 	thread_fphil[i].num_philo = i;
	// 	thread_fphil[i].col_fork = 0;
	// 	thread_fphil[i].check_eat = 0;
	// }
	// for(int j = 1; j <= param.number_of_philos; j++)
	// {
	// 	printf("max_forks: %d\n", param.number_of_forks);
	// 	printf("%d: col_fork: %d\n\n", j, thread_fphil[j].col_fork);
	// }
	// printf("\n\n");


	// for(int k = 1; k <= param.number_of_philos; k++)
	// 	pthread_create(&(threads[k]), NULL, taking_forks, &thread_fphil[k]);
	// for(int w = 1; w <= param.number_of_philos; w++)
	// 	pthread_join(threads[w], NULL);
	// for(int q = 1; q <= param.number_of_philos; q++)
	// {
	// 	printf("max_forks: %d\n", param.number_of_forks);
	// 	printf("%d: col_fork: %d\n\n", q, thread_fphil[q].col_fork);
	// 	printf("%d: check_eat: %lld\n\n", q, thread_fphil[q].check_eat);
	// }
	// printf("check: %d\n", param.check);
	// user_sleep(param.time_to_sleep);







}