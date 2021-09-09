/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:51:50 by fkenned           #+#    #+#             */
/*   Updated: 2021/08/25 18:51:52 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_eat(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (g_param.died == 0 && p->left_fork >= 0 && p->right_fork >= 0)
	{
		p->col_eat += 1;
		pthread_mutex_lock(&g_param.eat_death);
		if (g_param.died != 0)
			return (NULL);
		pthread_mutex_unlock(&g_param.eat_death);
		pthread_mutex_lock(&g_param.mutex);
		if (g_param.died == 0)
		{
			printf("%lld    ", check_time() - g_param.time_start);
			printf("%d    is eating\n", p->num_philo);
		}
		pthread_mutex_unlock(&g_param.mutex);
		p->last_eat = check_time();
		usleep(g_param.time_to_eat);
	}
	if (p->left_fork >= 0)
		pthread_mutex_unlock(&g_param.fork[p->left_fork]);
	if (p->right_fork >= 0)
		pthread_mutex_unlock(&g_param.fork[p->right_fork]);
	return (NULL);
}

int	ft_take(t_philo *p)
{
	pthread_mutex_lock(&g_param.eat_death);
	if (g_param.died != 0)
		return (1);
	pthread_mutex_unlock(&g_param.eat_death);
	pthread_mutex_lock(&g_param.mutex);
	if (g_param.died == 0)
	{
		printf("%lld    ", check_time() - g_param.time_start);
		printf("%d    has taken a fork\n", p->num_philo);
	}
	pthread_mutex_unlock(&g_param.mutex);
	return (0);
}

void	*take_forks(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->left_fork >= 0)
		pthread_mutex_lock(&g_param.fork[p->left_fork]);
	if (g_param.died == 0 && p->left_fork >= 0)
	{
		if (ft_take(p) == 1)
			return (NULL);
	}
	if (p->right_fork >= 0)
		pthread_mutex_lock(&g_param.fork[p->right_fork]);
	if (g_param.died == 0 && p->right_fork >= 0)
	{
		if (ft_take(p) == 1)
			return (NULL);
	}
	return (NULL);
}

void	*ft_sleep(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (g_param.died == 0 && p->col_eat != 0)
	{
		pthread_mutex_lock(&g_param.eat_death);
		if (g_param.died != 0)
			return (NULL);
		pthread_mutex_unlock(&g_param.eat_death);
		pthread_mutex_lock(&g_param.mutex);
		if (g_param.died == 0)
		{
			printf("%lld    ", check_time() - g_param.time_start);
			printf("%d    is sleeping\n", p->num_philo);
		}
		pthread_mutex_unlock(&g_param.mutex);
		usleep(g_param.time_to_sleep);
	}
	return (NULL);
}

void	*ft_thinking(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (g_param.died == 0 && p->col_eat != 0)
	{
		pthread_mutex_lock(&g_param.eat_death);
		if (g_param.died != 0)
			return (NULL);
		pthread_mutex_unlock(&g_param.eat_death);
		pthread_mutex_lock(&g_param.mutex);
		if (g_param.died == 0)
		{
			printf("%lld    ", check_time() - g_param.time_start);
			printf("%d    is thinking\n", p->num_philo);
		}
		pthread_mutex_unlock(&g_param.mutex);
	}
	return (NULL);
}
