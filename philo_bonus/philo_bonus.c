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

int main(int argc, char **argv)
{
	error(argc);
	parser(&g_param, argv);
	check_arguments(&g_param, argv);
	printf("number_of_philo: %d\n", g_param.number_of_philo);
	printf("time_to_die: %d\n", g_param.time_to_die);
	printf("time_to_eat: %d\n", g_param.time_to_eat);
	printf("time_to_sleep: %d\n", g_param.time_to_sleep);
	printf("must_eat: %d\n", g_param.must_eat);
}