#include "philo_new.h"

void	error(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}