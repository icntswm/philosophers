#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/time.h>

typedef struct	s_param
{
	int number_of_philos;
	int number_of_forks;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_eat;
	long long time_start;
	long long new_time;
	long long old_time;
}				t_param;

int		main(int argc, char **argv);
void	error(int argc);
int		ft_atoi(char *str);

#endif