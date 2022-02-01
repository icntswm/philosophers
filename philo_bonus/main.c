#include "philo_bonus.h"

void	life(t_philo *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	ph->last_eat = check_time();
	pthread_create(&ph->thread, NULL, &ft_check_death, ph);
	while (1)
	{
		take_forks(ph);
		ft_eat(ph);
		if (ph->col_eat == g_param.must_eat)
			break ;
		ft_sleeping(ph);
		ft_thinking(ph);
	}
	pthread_join(ph->thread, NULL);
	exit (0);
}

void	child_proc(void)
{
	int	i;

	i = 0;
	philo_init();
	while (i < g_param.num_of_philo)
	{
		g_param.ph[i].die = fork();
		if (g_param.ph[i].die == 0)
			life(&g_param.ph[i]);
		i++;
	}
	pthread_create(&g_param.check_die, NULL, &ft_check_par_death, &g_param);
	i = 0;
	while (i < g_param.num_of_philo)
	{
		waitpid(g_param.ph[i].die, NULL, 0);
		i++;
		if (i == g_param.num_of_philo)
			sem_post(g_param.kill);
	}
	pthread_join(g_param.check_die, NULL);
}

void	ft_free(void)
{
	int	i;

	i = 0;
	if (g_param.ph)
	{
		while (i < g_param.num_of_philo)
		{
			if (sem_unlink(g_param.ph[i].name_s) == -1)
				printf("lol\n");
			if (sem_close(g_param.ph[i].mutex) == -1)
				printf("kek\n");
			free(g_param.ph[i].name_s);
			g_param.ph[i].name_s = NULL;
			i++;
		}
		free(g_param.ph);
	}
	sem_unlink("sem_forks");
	sem_close(g_param.forks);
	sem_unlink("sem_mut");
	sem_close(g_param.mut);
	sem_unlink("sem_kill");
	sem_close(g_param.kill);
}

int	main(int argc, char **argv)
{
	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	init_sem_forks();
	child_proc();
	ft_free();
	return (0);
}
