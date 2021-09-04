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
	g_param->check_sleep = 0;
}

void	init_sem_forks(void)
{
	sem_unlink("sem_forks");
	g_param.forks = sem_open("sem_forks", O_CREAT, 0777, g_param.number_of_philo);
	sem_unlink("sem_mut");
	g_param.mut = sem_open("sem_mut", O_CREAT, 0777, 1);
	sem_unlink("thread_sleep");
	g_param.thread_sleep = sem_open("thread_sleep", O_CREAT, 0777, 0);
	sem_unlink("thread_eat");
	g_param.thread_eat = sem_open("thread_eat", O_CREAT, 0777, 0);
	sem_unlink("thread_die");
	g_param.thread_die = sem_open("thread_die", O_CREAT, 0777, 0);
}

void	philo_init(int pid)
{
	int i = 0;
	g_param.philo = (t_philo *)malloc(sizeof(t_philo) * g_param.number_of_philo);
	while (i < g_param.number_of_philo)
	{
		g_param.philo[i].num_philo = i + 1;
		g_param.philo[i].col_eat = 0;
		g_param.philo[i].last_eat = 0;
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


void	ft_kek(void	*philo)
{
	t_philo *ph;
	ph = (t_philo *)philo;
	while (ph->col_forks != 2)
	{
		sem_wait(g_param.forks);
		ph->col_forks += 1;
		printf("%lld   %d   has taken a fork | col_forks: %d\n", check_time() - g_param.time_start, ph->num_philo, ph->col_forks);
	}
	if (ph->col_forks == 2)
	{
		printf("%lld   %d   is eating\n", check_time() - g_param.time_start, ph->num_philo);
		ph->last_eat = check_time();
		user_sleep(g_param.time_to_sleep);
		sem_post(g_param.forks);
		sem_post(g_param.forks);
	}
	// printf("num_philo: %d col_eat: %d ", ph->num_philo, ph->col_eat);
	// printf("last_eat: %lld col_forks: %d\n", ph->last_eat, ph->col_forks);
	kill(ph->pid, 1);
}

void	*ft_lol(void	*kek)
{
	printf("tyt\n");
	user_sleep(2000);
	return(NULL);
}

void	child_proc(int pid)
{
	int i = 0;
	
	philo_init(pid);
	while (i < g_param.number_of_philo)
	{
		g_param.philo[i].pid = fork();
		ft_kek(&g_param.philo[i]);
		i++;
	}
	// user_sleep(5000);
	// pthread_create(&g_param.make_sleep, NULL, &ft_lol, &g_param);
	// pthread_join(g_param.make_sleep, NULL);
	exit (0);
}

void	*ft_make_sleep(void *sl)
{
	while (1)
	{
		sem_wait(g_param.thread_sleep);
		user_sleep(g_param.time_to_sleep);
		sem_post(g_param.forks);
		sem_post(g_param.forks);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pid_t	pid;

	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	init_sem_forks();
	// pthread_create(&g_param.make_sleep, NULL, &ft_make_sleep, &g_param);
	// pthread_create(&g_param.make_sleep, NULL, &ft_make_eat, &g_param);
	// pthread_create(&g_param.make_sleep, NULL, &ft_make_die, &g_param);
	

	pid = fork();
	if (pid == 0)
		child_proc(pid);
	waitpid(pid, NULL, 0);
	
	printf("check_sleep: %d\n", g_param.check_sleep);
	if (pid > 0)
		printf("\nchild ended\n");
	// pthread_join(g_param.make_sleep, NULL);
	// pthread_join(g_param.make_eat, NULL);
	// pthread_join(g_param.make_die, NULL);

	// int i = g_param.number_of_philo;
	// while (i > 0)
	// {
	// 	sem_wait(g_param.forks);
	// 	printf("i: %d\n", i);
	// 	i--;
	// }
	
	// sem_wait(g_param.forks);
	
	// int kek;
	// pid_t pid;
	// pid = fork();
	// if (pid == 0)
	// 	fork_proc(g_param.forks);
	// waitpid (pid, NULL, 0);
	// sem_wait(g_param.forks);
	// // printf("pid: %d\n", pid);
	// // sem_post(&sem1);
	printf("number_of_philo: %d\n", g_param.number_of_philo);
	// sem_post(g_param.forks);
	// sem_close(sem1);
	printf("time_to_die: %d\n", g_param.time_to_die);
	printf("time_to_eat: %d\n", g_param.time_to_eat);
	printf("time_to_sleep: %d\n", g_param.time_to_sleep);
	printf("must_eat: %d\n", g_param.must_eat);
	printf("time_start: %lld\n", g_param.time_start);
	return (0);
}