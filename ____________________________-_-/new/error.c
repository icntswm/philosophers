#include "philo_new.h"

void	error(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}

void	check_arguments(t_param *param, char **argv)
{
	if (param->number_of_philo <= 0 || param->time_to_die <= 0
		|| param->time_to_eat <= 0 || param->time_to_sleep <= 0)
	{
		write(1, "Error: negative or zero arguments\n", 34);
		exit(0);
	}
	if (param->number_of_philo > 200)
	{
		write(1, "Error: more than 200 philosophers\n", 35);
		exit(0);
	}
	if (param->time_to_die < 60 || param->time_to_eat < 60
		|| param->time_to_sleep < 60)
	{
		write(1, "Error: less than 60 milliseconds\n", 34);
		exit(0);
	}
	if (argv[5] && param->must_eat <= 0)
	{
		write(1, "Error: invalid fifth argument\n", 31);
		exit (0);
	}
}
