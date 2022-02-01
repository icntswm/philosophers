#include "philo.h"

int	ft_atoi(char *str)
{
	int	num;
	int	i;
	int	sign;

	sign = 0;
	i = 0;
	num = 0;
	if (str[i] == ' ' || str[i] == '\t' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	if (sign)
		num *= -1;
	return (num);
}
