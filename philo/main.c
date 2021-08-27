/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:52:00 by fkenned           #+#    #+#             */
/*   Updated: 2021/08/25 18:52:02 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void	*philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		if (p->col_eat == g_param.must_eat && g_param.number_of_philo > 1)
			break ;
		ft_sleep(philo);
		ft_thinking(philo);
		if ((p->left_fork < 0 || p->right_fork < 0 ) || g_param.died != 0)
		{
			if (p->left_fork < 0 || p->right_fork < 0)
			{
				while (g_param.died == 0)
					usleep (5);
			}
			break ;
		}
	}
	return (NULL);
}

void	ft_free(t_param *g_param)
{
	int	i;

	if (g_param->fork)
	{
		i = 0;
		while (i < g_param->number_of_philo)
		{
			pthread_mutex_destroy(&g_param->fork[i]);
			i++;
		}
		free(g_param->fork);
	}
	pthread_mutex_destroy(&g_param->mutex);
	pthread_mutex_destroy(&g_param->eat_death);
	if (g_param->philo)
		free(g_param->philo);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	philo_init(&g_param);
	mutex_init(&g_param);
	pthread_create(&g_param.die, NULL, thread_death, &g_param);
	while (i < g_param.number_of_philo)
	{
		if (g_param.philo[i].num_philo % 2 == 0)
			usleep(200);
		pthread_create(&g_param.philo[i].tread, NULL, &life, &g_param.philo[i]);
		i++;
	}
	i = 0;
	while (i < g_param.number_of_philo)
	{
		pthread_join(g_param.philo[i].tread, NULL);
		i++;
	}
	pthread_join(g_param.die, NULL);
	ft_free(&g_param);
	return (0);
}
