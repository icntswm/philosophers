#include "philo_bonus.h"

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
