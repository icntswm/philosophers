#include "philo_new.h"

void	*life(void	*philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		if (p->col_eat == param.must_eat && param.number_of_philo > 1)
			break ;
		ft_sleep(philo);
		ft_thinking(philo);
		if ((p->left_fork == 0 || p->right_fork == 0 ) || param.died != 0)
		{
			if (p->left_fork == 0 || p->right_fork == 0)
			{
				while (param.died == 0)
					usleep (5);
			}
			if (param.died == p->num_philo)
				printf("%lld    %d    died\n", param.time_end, param.died);
			break ;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	error(argc);
	parser(&param, argv);
	check_arguments(&param, argv);
	philo_init(&param);
	mutex_init(&param);
	while (i <= param.number_of_philo)
	{
		if (param.philo[i].num_philo % 2 == 0)
			usleep(200);
		pthread_create(&param.tread[i], NULL, &life, &param.philo[i]);
		i++;
	}
	pthread_create(&param.die, NULL, thread_death, &param);
	i = 1;
	while (i <= param.number_of_philo)
	{
		pthread_join(param.tread[i], NULL);
		i++;
	}
	pthread_join(param.die, NULL);
}
