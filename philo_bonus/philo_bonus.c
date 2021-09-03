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
}


sem_t *sem1;
sem_t *sem2;

void	fork_proc(sem_t *sem1)
{
	sem_wait(sem1);
	printf("kek\n");
	printf("lol\n");
	sem_post(sem1);
	exit(0);
}

int main(int argc, char **argv)
{
	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	sem1 = sem_open("/sem_forks", O_CREAT, 644, 7);
	int kek;
	sem_getvalue(sem1, &kek);
	printf("kek: %d\n", kek);
	// sem_post(sem1);
	// sem_init(&sem1, 0, 1);
	pid_t pid;
	pid = fork();
	if (pid == 0)
		fork_proc(sem1);
	waitpid (pid, NULL, 0);
	sem_wait(sem1);
	// printf("pid: %d\n", pid);
	// sem_post(&sem1);
	printf("number_of_philo: %d\n", g_param.number_of_philo);
	sem_post(sem1);
	// sem_close(sem1);
	sem_destroy(sem1);
	// printf("time_to_die: %d\n", g_param.time_to_die);
	// printf("time_to_eat: %d\n", g_param.time_to_eat);
	// printf("time_to_sleep: %d\n", g_param.time_to_sleep);
	// printf("must_eat: %d\n", g_param.must_eat);
	return (0);
}