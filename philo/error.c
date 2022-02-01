#include "philo.h"

void	error(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}

void	check_arguments(t_param *g_param, char **argv)
{
	if (g_param->number_of_philo <= 0 || g_param->time_to_die <= 0
		|| g_param->time_to_eat <= 0 || g_param->time_to_sleep <= 0)
	{
		write(1, "Error: negative or zero arguments\n", 34);
		exit(0);
	}
	if (g_param->number_of_philo > 200)
	{
		write(1, "Error: more than 200 philosophers\n", 35);
		exit(0);
	}
	if (g_param->time_to_die < 60 || g_param->time_to_eat < 60
		|| g_param->time_to_sleep < 60)
	{
		write(1, "Error: less than 60 milliseconds\n", 34);
		exit(0);
	}
	if (argv[5] && g_param->must_eat <= 0)
	{
		write(1, "Error: invalid fifth argument\n", 31);
		exit (0);
	}
}
