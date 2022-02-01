#include "philo.h"

int	check_death(t_param *p, int i)
{
	pthread_mutex_lock(&g_param.eat_death);
	p->time_end = check_time();
	if (p->time_end - p->philo[i].last_eat > p->time_to_die)
	{
		p->died = p->philo[i].num_philo;
		printf("%lld    %d    died\n", p->time_end - p->time_start, p->died);
		pthread_mutex_unlock(&g_param.eat_death);
		return (1);
	}
	pthread_mutex_unlock(&g_param.eat_death);
	return (0);
}

void	*thread_death(void *par)
{
	t_param	*p;
	int		i;

	p = (t_param *)par;
	while (1)
	{
		i = 0;
		while (i < p->number_of_philo)
		{
			if (check_death(p, i) == 1)
				return (NULL);
			if (p->must_eat != 0 && p->philo[i].col_eat == p->must_eat)
				p->check_eat_for_thrdeath += 1;
			if (p->check_eat_for_thrdeath == p->number_of_philo)
				return (NULL);
			i++;
		}
		if (p->number_of_philo > 0 && p->number_of_philo <= 70)
			usleep (10);
		else if (p->number_of_philo > 70 && p->number_of_philo <= 130)
			usleep (1000);
		else if (p->number_of_philo > 130 && p->number_of_philo <= 200)
			usleep (5000);
	}
	return (NULL);
}
