#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h> //compile with flag '-lpthread'

// typedef struct	s_pars
// {
// 	int number_of_philos;
// 	int time_to_die;
// 	int time_to_eat;
// 	int time_to_sleep;
// 	int max_eat;
// }				t_pars;

typedef struct s_glob
{
	int number_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int max_eat;
	int check_eating;
	long long time_start;
	pthread_mutex_t	col_fork;
}				t_glob;

typedef struct s_phil
{
	int num_philo;
	int col_forks;
	int	poel;
}				t_philo;


int		main(int argc, char **argv);
void	error(int argc);
int		ft_atoi(char *str);

#endif