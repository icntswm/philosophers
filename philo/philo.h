/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkenned <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:53:25 by fkenned           #+#    #+#             */
/*   Updated: 2021/08/25 18:53:27 by fkenned          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	tread;
	int			col_eat;
	int			num_philo;
	int			left_fork;
	int			right_fork;
	long long	last_eat;
}				t_philo;

typedef struct s_param
{
	long long		time_start;
	long long		time_end;
	int				check_eat_for_thrdeath;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				died;
	t_philo			*philo;
	pthread_t		die;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_death;
}				t_param;

t_param	g_param;

int			main(int argc, char **argv);

void		error(int argc);
void		check_arguments(t_param *param, char **argv);

int			ft_atoi(char *str);
long long	check_time(void);
void		user_sleep(long long time);

void		*take_forks(void *philo);
void		*ft_eat(void *philo);
void		*ft_sleep(void *philo);
void		*ft_thinking(void *philo);

void		parser(t_param *param, char **argv);
void		philo_init(t_param *param);
void		mutex_init(t_param *param);

void		*thread_death(void *par);

#endif
