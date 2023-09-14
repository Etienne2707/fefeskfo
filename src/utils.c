#include "philosophers.h"


int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;
	char *str2;

	i = 0;
	sign = 1;
	result = 0;
	str2 = (char *)str;
	while ((str2[i] >= 9 && str2[i] <= 13 )|| str2[i] == 32)
		i++;
	if (str2[i] == '+')
		i++;
	else if (str2[i] == '-')
	{
		i++;
		sign = sign * - 1;
	}
	while (str2[i] >= '0' && str2[i] <= '9' && str2[i] != '\0')
	{
		result *= 10;
		result = result + str2[i] - '0';
		i++;
	}
	return (result * sign);
}

int	print(t_philo *philo, char *str)
{
	t_info *info;
	size_t	t;

	info = get_info();
	pthread_mutex_lock(&info->print_lock);
	if ((die_checker(philo) == 0 && (strcmp("Is died", str) != 0)) 
		|| (philo->nb_eat == 0 && (strcmp("Is eating", str) != 0)))
	{
		pthread_mutex_unlock(&info->print_lock);
		return (0);
	}
	t = get_current_time() - info->time_start;
	printf("%ld %d %s\n", t, philo->id, str);
	pthread_mutex_unlock(&info->print_lock);
}

int	die_checker(t_philo *philo)
{
	t_info *info;

	info = get_info();
	pthread_mutex_lock(&info->dead_lock);
	if (info->die == 0)
	{
		pthread_mutex_unlock(&info->dead_lock);
		return (0);
	}
	pthread_mutex_unlock(&info->dead_lock);
	return (1);
}

int	ft_usleep(long int time)
{
	long int	start;

	start = get_current_time();
	while (get_current_time() - start < time)
	{
		usleep(10);
	}
	return (1);
}

// Gets the current time in time

long int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
