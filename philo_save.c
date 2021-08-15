#include "philo.h"
#include <pthread.h> //compile with flag '-lpthread'

t_param param;
pthread_mutex_t mutex;

void	param_init(t_param *param)
{
	param->number_of_philos = 0;
	param->number_of_forks = 0;
	param->time_to_die = 0;
	param->time_to_eat = 0;
	param->time_to_sleep = 0;
	param->max_eat = 0;
	param->time_start = 0;
	param->check = 0;
}

void	fphil_init(t_fphil *fphil)
{
	fphil->check_eat = 0;
	fphil->col_fork = 0;
}

long long check_time()
{
	struct timeval tv;
	long long milisec;

	milisec = 0;
	gettimeofday(&tv, NULL);
	milisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milisec);
}

void	parser(char **argv, t_param *param)
{
	if (argv[1] != NULL)
	{
		param->number_of_philos = ft_atoi(argv[1]);
		param->number_of_forks = param->number_of_philos;
	}
	if (argv[2] != NULL)
		param->time_to_die = ft_atoi(argv[2]);
	if (argv[3] != NULL)
		param->time_to_eat = ft_atoi(argv[3]);
	if (argv[4] != NULL)
		param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		param->max_eat = ft_atoi(argv[5]);
	param->time_start = check_time();
}

void	user_sleep(long long time) //замена usleep, тк usleep периодически возвращает время с задержкой от 1 до 7мс
{
	long long	save_time;
	
	save_time = check_time();
	while (1)
	{
		if (check_time() == (save_time + time))
			break;
	}
}


void	*ft_sleep(void	*thread_fphil)
{
	t_fphil *p;

	p = (t_fphil *)thread_fphil;
	printf("%-lld    %d is sleeping\n", check_time() - param.time_start, p->num_philo);
	user_sleep(param.time_to_sleep);
	// user_sleep(slp);
	return (NULL);
}

void	*ft_thinking(void	*thread_fphil)
{
	t_fphil *p;
	long long check;
	p = (t_fphil *)thread_fphil;
	printf("%-lld    %d is thinking\n", check_time() - param.time_start, p->num_philo);
	check = check_time();
	// while (check_time() != (check + param.time_to_die))
		user_sleep(param.time_to_die - param.time_to_eat - param.time_to_sleep);
	return (NULL);
}

void	*ft_eat(void	*thread_fphil)
{
	t_fphil *p;

	p = (t_fphil *)thread_fphil;
	p->col_fork = 0;
	printf("%-lld    %d is eating\n", check_time() - param.time_start, p->num_philo);
	p->check_eat = check_time() - param.time_start;
	param.check += 1;
	user_sleep(param.time_to_eat);
	pthread_mutex_unlock(&mutex);
	param.number_of_forks += 2;
	// pthread_mutex_unlock(&mutex);
	ft_sleep(&(*thread_fphil));
	ft_thinking(&(*thread_fphil));
	// user_sleep(eat);
	return (NULL);
}

void	*taking_forks(void	*thread_fphil)
{
	t_fphil *p;

	p = (t_fphil *)thread_fphil;
	if (param.number_of_forks == 0)
		pthread_mutex_lock(&mutex);
	if (param.number_of_forks > 0)
	{
		if (p->col_fork != 2 && param.number_of_forks > 0)
		{
			while (p->col_fork != 2 && param.number_of_forks > 0)
			{
				p->col_fork++;
				param.number_of_forks--;
				printf("%-lld    %d has taken a fork\n", check_time() - param.time_start, p->num_philo);
				if (p->col_fork == 2)
					ft_eat(&(*thread_fphil));
			}
		}
	}
	return (NULL);
}

void	*eating(void	*thread_fphil)
{
	t_fphil *p;

	p = (t_fphil *)thread_fphil;
	while (1)
	{
		taking_forks(&(*thread_fphil));
		// if (p->col_fork == 2)
		// 	ft_eat(&(*thread_fphil));
		// else
		// 	pthread_mutex_lock(&mutex);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	error(argc);
	param_init(&param);
	parser(argv, &param);

	pthread_t	*threads;
	t_fphil		*thread_fphil;
	pthread_mutex_init(&mutex, NULL);

	threads = (pthread_t *)malloc(sizeof(pthread_t) * param.number_of_philos);
	thread_fphil = (t_fphil *)malloc(sizeof(t_fphil) * param.number_of_philos);
	for(int i = 1; i <= param.number_of_philos; i++)
	{
		thread_fphil[i].num_philo = i;
		thread_fphil[i].col_fork = 0;
		thread_fphil[i].check_eat = 0;
	}
	for(int j = 1; j <= param.number_of_philos; j++)
	{
		printf("max_forks: %d\n", param.number_of_forks);
		printf("%d: col_fork: %d\n\n", j, thread_fphil[j].col_fork);
	}
	printf("\n\n");


	for(int k = 1; k <= param.number_of_philos; k++)
		pthread_create(&(threads[k]), NULL, eating, &thread_fphil[k]);
	for(int w = 1; w <= param.number_of_philos; w++)
		pthread_join(threads[w], NULL);
	for(int q = 1; q <= param.number_of_philos; q++)
	{
		printf("max_forks: %d\n", param.number_of_forks);
		printf("%d: col_fork: %d\n\n", q, thread_fphil[q].col_fork);
		printf("%d: check_eat: %lld\n\n", q, thread_fphil[q].check_eat);
	}
	printf("check: %d\n", param.check);
	// user_sleep(param.time_to_sleep);







	// printf("number_of_philosophers: %d\n", param.number_of_philos);
	// printf("number_of_forks: %d\n", param.number_of_forks);
	// printf("time_to_die: %d\n", param.time_to_die);
	// printf("time_to_eat: %d\n", param.time_to_eat);
	// printf("time_to_sleep: %d\n", param.time_to_sleep);
	// printf("max_eat: %d\n", param.max_eat);
}