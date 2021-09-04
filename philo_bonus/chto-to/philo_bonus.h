#ifndef PHILO_BONUS
# define PHILO_BONUS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

typedef struct s_philo
{
	pid_t	pid;
	// sem_t	*thread_sleep;
	int col_eat;
	int col_forks;
	int num_philo;
	long long last_eat;
}				t_philo;


typedef struct s_param
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		time_start;
	int				check_sleep;
	pthread_t		make_die;
	pthread_t		make_sleep;
	pthread_t 		make_eat;
	sem_t			*thread_sleep;
	sem_t			*thread_eat;
	sem_t			*thread_die;
	sem_t			*forks;
	sem_t			*mut;
	t_philo			*philo;
}				t_param;

t_param	g_param;

int main(int argc, char **argv);
int	ft_atoi(char *str);
//error
void	error(int argc);
void	check_arguments(t_param *g_param, char **argv);

//time
void	user_sleep(long long time);
long long	check_time(void);

#endif