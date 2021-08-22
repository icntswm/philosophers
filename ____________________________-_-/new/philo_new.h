#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int	col_eat;
	int num_philo;
	int left_fork;
	int right_fork;
	long long last_eat;
}				t_philo;

typedef struct s_param
{
	long long		time_start;
	int 			number_of_philo;
    int 			time_to_die;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			must_eat;
	int 			number_must_eat;
	t_philo			*philo;
	pthread_t		*tread;
	pthread_t		die;
	int died;
	pthread_mutex_t	*fork;
	// pthread_mutex_t	mutex;
}				t_param;

t_param param;

int main(int argc, char **argv);
void	error(int argc);
void	check_arguments(t_param *param, char **argv);
int	ft_atoi(char *str);
long long check_time();
void	user_sleep(long long time);


#endif