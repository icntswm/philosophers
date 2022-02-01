#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_philo
{
	pid_t		die;
	pthread_t	thread;
	sem_t		*mutex;
	char		*name_s;
	int			num_philo;
	int			col_eat;
	long long	last_eat;
}				t_philo;

typedef struct s_param
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		time_start;
	pthread_t		check_die;
	sem_t			*kill;
	sem_t			*forks;
	sem_t			*mut;
	t_philo			*ph;
}				t_param;

t_param	g_param;

int			main(int argc, char **argv);
//pars/init
void		parser(t_param *g_param, char **argv);
void		init_sem_forks(void);
void		philo_init(void);
//life pocess
void		take_forks(t_philo *ph);
void		ft_eat(t_philo *ph);
void		ft_sleeping(t_philo *ph);
void		ft_thinking(t_philo *ph);
//error
void		error(int argc);
void		check_arguments(t_param *g_param, char **argv);
//free
void		ft_free(void);
//time
//void	user_sleep(long long time);
long long	check_time(void);
//other
int			ft_atoi(char *str);
char		*ft_itoa(int n);
int			ft_strlen(char *str);
//threads_death
void		*ft_check_death(void	*philo);
void		*ft_check_par_death(void	*g_par);

#endif
