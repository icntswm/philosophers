/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:14:15 by fkenned           #+#    #+#             */
/*   Updated: 2021/09/09 15:14:28 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_check_death(void	*philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		sem_wait(ph->mutex);
		if (g_param.must_eat != 0 && ph->col_eat == g_param.must_eat)
			break ;
		if (check_time() - ph->last_eat > g_param.time_to_die)
		{
			sem_wait(g_param.mut);
			printf("%lld   ", check_time() - g_param.time_start);
			printf("%d   died\n", ph->num_philo);
			sem_post(g_param.kill);
			break ;
		}
		sem_post(ph->mutex);
		if (g_param.num_of_philo > 0 && g_param.num_of_philo <= 70)
			usleep(50);
		else if (g_param.num_of_philo > 70 && g_param.num_of_philo <= 130)
			usleep(500);
		else if (g_param.num_of_philo > 130 && g_param.num_of_philo <= 200)
			usleep(5000);
	}
	return (NULL);
}

void	*ft_check_par_death(void	*g_par)
{
	t_param	*g;
	int		i;

	i = 0;
	g = (t_param *)g_par;
	sem_wait(g->kill);
	while (i < g->num_of_philo)
	{
		kill(g->ph[i].die, SIGKILL);
		i++;
	}
	return (NULL);
}
