#include "philo.h"

void	error(int argc)
{
	if (argc == 1)
	{
		write(1, "Error: no arguments\n", 20);
		exit(0);
	}
}