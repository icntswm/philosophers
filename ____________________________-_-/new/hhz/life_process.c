#include "philo.h"

void	*ft_eat(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (param.died == 0 && p->left_fork != 0 && p->right_fork != 0)
	{
		p->col_eat += 1;
		pthread_mutex_lock(&param.mutex);
		printf("%lld    ", check_time() - param.time_start);
		printf("%d    is eating\n", p->num_philo);
		pthread_mutex_unlock(&param.mutex);
		p->last_eat = check_time();
		user_sleep(param.time_to_eat);
	}
	pthread_mutex_unlock(&param.fork[p->left_fork]);
	pthread_mutex_unlock(&param.fork[p->right_fork]);
	return (NULL);
}

void	*take_forks(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&param.fork[p->left_fork]);
	if (param.died == 0 && p->left_fork != 0)
	{
		pthread_mutex_lock(&param.mutex);
		printf("%lld    ", check_time() - param.time_start);
		printf("%d    has taken a left fork\n", p->num_philo);
		pthread_mutex_unlock(&param.mutex);
	}
	pthread_mutex_lock(&param.fork[p->right_fork]);
	if (param.died == 0 && p->right_fork != 0)
	{
		pthread_mutex_lock(&param.mutex);
		printf("%lld    ", check_time() - param.time_start);
		printf("%d    has taken a right fork\n", p->num_philo);
		pthread_mutex_unlock(&param.mutex);
	}
	return (NULL);
}

void	*ft_sleep(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (param.died == 0 && p->col_eat != 0)
	{
		pthread_mutex_lock(&param.mutex);
		printf("%lld    ", check_time() - param.time_start);
		printf("%d    is sleeping\n", p->num_philo);
		pthread_mutex_unlock(&param.mutex);
		user_sleep(param.time_to_sleep);
	}
	return (NULL);
}

void	*ft_thinking(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (param.died == 0 && p->col_eat != 0)
	{
		pthread_mutex_lock(&param.mutex);
		printf("%lld    ", check_time() - param.time_start);
		printf("%d    is thinking\n", p->num_philo);
		pthread_mutex_unlock(&param.mutex);
	}
	return (NULL);
}
