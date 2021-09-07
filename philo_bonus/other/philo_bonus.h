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
	int num_philo;
	int col_eat;
	long long last_eat;
	pid_t	die;
	pthread_t	thread;
	sem_t	*mutex;
	char *name_sem;
}				t_philo;


typedef struct s_param
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		time_start;
	pthread_t		check_die;
	sem_t			*kill;
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
void	ft_free(void);
//time
//void	user_sleep(long long time);
long long	check_time(void);
char	*ft_itoa(int n);
int ft_strlen(char *str);

#endif