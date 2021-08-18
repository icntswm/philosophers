#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int num_philo;
    int eating;
    int col_forks;
	// struct s_strc	*strc;
}				t_philo;

typedef struct s_strc
{
	long long		time_start;
	int 			number_of_philo;
    int 			time_to_die;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			must_eat;
	int				number_of_forks;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	dead;
	pthread_mutex_t	forks;
	pthread_mutex_t	forks1;
	int check;
}				t_strc;

t_strc strc;




int main(int argc, char **argv);
void	error(int argc);
int	ft_atoi(char *str);


#endif