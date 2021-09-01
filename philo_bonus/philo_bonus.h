#ifndef PHILO_BONUS
# define PHILO_BONUS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct s_param
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
}				t_param;

t_param	g_param;

int main(int argc, char **argv);
int	ft_atoi(char *str);
//error
void	error(int argc);
void	check_arguments(t_param *g_param, char **argv);

#endif