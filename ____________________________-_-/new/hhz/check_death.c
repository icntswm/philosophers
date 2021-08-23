#include "philo.h"

void	*thread_death(void *par)
{
	t_param	*p;
	int		i;

	p = (t_param *)par;
	i = 1;
	while (1)
	{
		while (i <= p->number_of_philo)
		{
			p->time_end = check_time() - param.time_start;
			if (check_time() - p->philo[i].last_eat > p->time_to_die)
			{
				p->died = p->philo[i].num_philo;
				return (NULL);
			}
			if (p->must_eat != 0 && p->philo[i].col_eat == param.must_eat)
				p->check_eat_for_thrdeath += 1;
			if (p->check_eat_for_thrdeath == p->number_of_philo)
				return (NULL);
			i++;
		}
		usleep (5);
		i = 1;
	}
	return (NULL);
}
