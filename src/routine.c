#include "philosophers.h"

int	think(t_philo *philo, t_info *info)
{
	if (philo->nb_eat == 0 || die_checker(philo) == 0)
		return (0);
	print(philo, "Is thinking");
	ft_usleep(1);
}

int	sleepfort(t_philo *philo)
{
	t_info *info;

	info = get_info();
	if (philo->nb_eat == 0 || die_checker(philo) == 0)
		return (0);
	print(philo, "Is sleeping");
	ft_usleep(info->time_sleep);
}
	 
	

int	take_fork(t_philo *philo)
{
	if (philo->nb_eat == 0 || die_checker(philo) == 0)
		return (0);
	pthread_mutex_lock(&philo->forks_l);
	print(philo ,"Has taking a fork ");
	pthread_mutex_lock(philo->forks_r);
	print(philo ,"Has taking a fork ");
}

int	eat(t_philo *philo)
{
	t_info *info;
	info = get_info();

	if (philo->nb_eat == 0 || die_checker(philo) == 0)
		return (0);
	pthread_mutex_lock(&philo->time_lock);
	philo->last_eat = get_current_time() - info->time_start;
	pthread_mutex_unlock(&philo->time_lock);
	pthread_mutex_lock(&philo->lock_eat);
	philo->nb_eat--;
	print(philo, "Is eating");
	pthread_mutex_unlock(&philo->lock_eat);
	ft_usleep(info->time_eat);	
}

void *routine_philo(void *data)
{
	t_info		*info;
	t_philo     *philo;
	
	philo = (t_philo *)data;
	info = get_info();
	if (info->nb_philo == 1)
	{
		print(philo, "Has taking a fork");
		ft_usleep(info->time_die);
		print(philo, "Is died");
		return (0);
	}
	if (philo->id % 2)
		ft_usleep(1);
	while (die_checker(philo) != 0)
	{
		take_fork(philo);
		eat(philo);
		pthread_mutex_unlock(&philo->forks_l);
		pthread_mutex_unlock(philo->forks_r);
		sleepfort(philo);
		think(philo, info);
	}
	return (NULL);
}