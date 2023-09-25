/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:49:36 by educlos           #+#    #+#             */
/*   Updated: 2023/09/25 21:06:27 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_dead(t_philo *philo, t_info *info, int i)
{
	pthread_mutex_unlock(&philo[i].time_lock);
	pthread_mutex_lock(&info->dead_lock);
	info->die = 0;
	pthread_mutex_unlock(&info->dead_lock);
	print(&philo[i], "Is died");
	return (1);
}

int	full_eat(t_philo *philo, t_info *info)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_lock(&philo[i].lock_eat);
		if (philo[i].nb_eat == 0)
			counter++;
		i++;
	}
	pthread_mutex_unlock(&philo[i].lock_eat);
	if (counter == i)
		info->die = 0;
	return (1);
}

int	die_monitor(t_philo *philo, t_info *info)
{
	int	i;

	while (info->die == 1)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			pthread_mutex_lock(&philo[i].time_lock);
			if (get_current_time() - info->time_start
				- philo[i].last_eat >= info->time_die)
			{
				print_dead(philo, info, i);
				return (0);
			}
			full_eat(philo, info);
			pthread_mutex_unlock(&philo[i].time_lock);
			i++;
		}
		usleep(500);
	}
	return (1);
}
