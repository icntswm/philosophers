#include "philo_bonus.h"

void	parser(t_param *g_param, char **argv)
{
	g_param->number_of_philo = ft_atoi(argv[1]);
	g_param->time_to_die = ft_atoi(argv[2]);
	g_param->time_to_eat = ft_atoi(argv[3]);
	g_param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_param->must_eat = ft_atoi(argv[5]);
	else
		g_param->must_eat = 0;
	g_param->time_start = check_time();
	g_param->counter = 0;
}

void	init_sem_forks(void)
{
	sem_unlink("sem_forks");
	g_param.forks = sem_open("sem_forks", O_CREAT, 0777, g_param.number_of_philo);
	sem_unlink("sem_mut");
	g_param.mut = sem_open("sem_mut", O_CREAT, 0777, 1);
	sem_unlink("sem_die");
	g_param.die = sem_open("sem_die", O_CREAT, 0777, 1);
	sem_unlink("sem_kill");
	g_param.kill = sem_open("sem_kill", O_CREAT, 0777, 0);
}

void	philo_init(void)
{
	int i = 0;
	g_param.philo = (t_philo *)malloc(sizeof(t_philo) * g_param.number_of_philo);
	while (i < g_param.number_of_philo)
	{
		g_param.philo[i].num_philo = i + 1;
		g_param.philo[i].col_eat = 0;
		g_param.philo[i].last_eat = check_time();
		g_param.philo[i].col_forks = 0;
		i++;
	}
	// i = 0;
	// while (i < g_param.number_of_philo)
	// {
	// 	printf("i: %d -- num_philo: %d col_eat: %d ", i, g_param.philo[i].num_philo, g_param.philo[i].col_eat);
	// 	printf("last_eat: %lld col_forks: %d\n", g_param.philo[i].last_eat, g_param.philo[i].col_forks);
	// 	i++;
	// }
}

void	*ft_check_death(void	*philo)
{
	t_philo *ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (g_param.must_eat != 0 && ph->col_eat == g_param.must_eat)
		{
			// printf("----> %d %d\n", ph->num_philo, ph->col_eat);
			break ;
		}
		if (check_time() - ph->last_eat > g_param.time_to_die)
		{
			sem_wait(g_param.die);
			printf("%lld   %d   died\n", check_time() - g_param.time_start, ph->num_philo);
			sem_post(g_param.kill);
		}
		usleep(50);
	}
	return (NULL);
}

void	take_forks(t_philo *ph)
{
	sem_wait(g_param.forks);
	sem_wait(g_param.die);
	printf("%lld   %d   has taken a fork\n", check_time() - g_param.time_start, ph->num_philo);
	sem_post(g_param.die);
	ph->col_forks++;
	sem_wait(g_param.forks);
	sem_wait(g_param.die);
	printf("%lld   %d   has taken a fork\n", check_time() - g_param.time_start, ph->num_philo);
	sem_post(g_param.die);
	ph->col_forks++;
}

void	ft_thinking(t_philo *ph)
{
	sem_wait(g_param.die);
	printf("%lld   %d   is thinking\n", check_time() - g_param.time_start, ph->num_philo);
	sem_post(g_param.die);
	ph->col_forks = 0;
}

void	ft_sleeping(t_philo *ph)
{
	sem_wait(g_param.die);
	printf("%lld   %d   is sleeping\n", check_time() - g_param.time_start, ph->num_philo);
	sem_post(g_param.die);
	user_sleep(g_param.time_to_sleep);
}

void	ft_eat(t_philo *ph)
{
	if (ph->col_forks == 2)
	{
		ph->col_eat++;
		sem_wait(g_param.die);
		printf("%lld   %d   is eating | col_eat: %d\n", check_time() - g_param.time_start, ph->num_philo, ph->col_eat);
		sem_post(g_param.die);
		ph->last_eat = check_time();
		user_sleep(g_param.time_to_eat);
		sem_post(g_param.forks);
		sem_post(g_param.forks);
	}
}

void	life(t_philo *philo)
{
	// printf("+ | %d %lld\n\n", philo->num_philo, philo->last_eat);
	t_philo *ph;

	ph = (t_philo *)philo;
	pthread_create(&philo->thread, NULL, &ft_check_death, philo);
	while (1)
	{
		take_forks(ph);
		ft_eat(ph);
		if (ph->col_eat == g_param.must_eat)
			break ;
		ft_sleeping(ph);
		ft_thinking(ph);
	}
	pthread_join(philo->thread, NULL);
	exit (0);
}

void *ft_check_par_death(void	*g_par)
{
	int i = 0;
	sem_wait(g_param.kill);
	while (i < g_param.number_of_philo)
	{
		kill(g_param.philo[i].pid, 1);
		i++;
	}
	
	return (NULL);
}

void	child_proc(void)
{
	int i = 0;
	
	philo_init();
	while (i < g_param.number_of_philo)
	{
		// usleep(200);
		g_param.philo[i].pid = fork();
		if (g_param.philo[i].pid == 0)
		{
			life(&g_param.philo[i]);
		}
		i++;
	}
	pthread_create(&g_param.check_die, NULL, &ft_check_par_death, &g_param);
	i = 0;
	while (i < g_param.number_of_philo)
	{
		waitpid(g_param.philo[i].pid, NULL, 0);
		i++;
	}
	if (i == g_param.number_of_philo )
	{
		sem_post(g_param.kill);
		i = 0;
	}
	pthread_join(g_param.check_die, NULL);
}

int main(int argc, char **argv)
{
	pid_t	pid;

	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	init_sem_forks();

	child_proc();
	

	// printf("number_of_philo: %d\n", g_param.number_of_philo);
	// printf("time_to_die: %d\n", g_param.time_to_die);
	// printf("time_to_eat: %d\n", g_param.time_to_eat);
	// printf("time_to_sleep: %d\n", g_param.time_to_sleep);
	// printf("must_eat: %d\n", g_param.must_eat);
	// printf("time_start: %lld\n", g_param.time_start);
	return (0);
}