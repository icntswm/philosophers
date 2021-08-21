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
	int left_fork;
	int right_fork;
	int eating;
}				t_philo;

typedef struct s_param
{
	long long		time_start;
	int 			number_of_philo;
    int 			time_to_die;
    int 			time_to_eat;
    int 			time_to_sleep;
    int 			must_eat;
	int check;
	t_philo			*philo;
	pthread_t		*tread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
}				t_param;

t_param param;

int main(int argc, char **argv);
void	error(int argc);
int	ft_atoi(char *str);
long long check_time();
void	user_sleep(long long time);


#endif