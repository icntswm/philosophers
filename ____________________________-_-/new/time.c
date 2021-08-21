#include "philo_new.h"

long long check_time()
{
	struct timeval tv;
	long long milisec;

	milisec = 0;
	gettimeofday(&tv, NULL);
	milisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (milisec);
}

void	user_sleep(long long time)
{
	long long	save_time;
	
	save_time = check_time();
	while (1)
	{
		if (check_time() == (save_time + time))
			break;
	}
}