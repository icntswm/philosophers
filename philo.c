#include "philo.h"

void	struct_init(t_param *param)
{
	param->number_of_philos = 0;
	param->number_of_forks = 0;
	param->time_to_die = 0;
	param->time_to_eat = 0;
	param->time_to_sleep = 0;
	param->max_eat = 0;
	param->time_start = 0;
	param->old_time = 0;
}

long long check_time()
{
	struct timeval tv;
	long long milisec;

	milisec = 0;
	gettimeofday(&tv, NULL);
	milisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	// printf("milisec: %lld\n", milisec);
	return (milisec);
}

void	parser(char **argv, t_param *param)
{
	if (argv[1] != NULL)
	{
		param->number_of_philos = ft_atoi(argv[1]);
		param->number_of_forks = param->number_of_philos;
	}
	if (argv[2] != NULL)
		param->time_to_die = ft_atoi(argv[2]);
	if (argv[3] != NULL)
		param->time_to_eat = ft_atoi(argv[3]);
	if (argv[4] != NULL)
		param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		param->max_eat = ft_atoi(argv[5]);
	param->time_start = check_time();
	param->old_time = check_time();
}

int main(int argc, char **argv)
{
	t_param param;

	error(argc);
	struct_init(&param);
	parser(argv, &param);
	if (check_time() != param.time_start)
		param.new_time = check_time() - param.time_start;
	else
		param.new_time = 0;
	printf("new_time: %lld\n", param.new_time);
	printf("number_of_philosophers: %d\n", param.number_of_philos);
	printf("number_of_forks: %d\n", param.number_of_forks);
	printf("time_to_die: %d\n", param.time_to_die);
	printf("time_to_eat: %d\n", param.time_to_eat);
	printf("time_to_sleep: %d\n", param.time_to_sleep);
	printf("max_eat: %d\n", param.max_eat);
	printf("old_time: %lld\n", param.old_time);
	if (check_time() != param.time_start)
		param.new_time = check_time() - param.time_start;
	else
		param.new_time = 0;
	printf("new_time: %lld\n", param.new_time);
}