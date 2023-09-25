/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:49:26 by educlos           #+#    #+#             */
/*   Updated: 2023/09/20 18:16:03 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_mutex_init(&philo[i].forks_l, NULL))
			return (-1);
		if (pthread_mutex_init(philo[i].forks_r, NULL))
			return (-1);
		if (pthread_mutex_init(&philo[i].time_lock, NULL))
			return (-1);
		if (pthread_mutex_init(&philo[i].lock_eat, NULL))
			return (-1);
		i++;
	}
	pthread_mutex_init(&info->eat_lock, NULL);
	pthread_mutex_init(&info->print_lock, NULL);
	pthread_mutex_init(&info->dead_lock, NULL);
	return (1);
}

int	init_thread(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&philo[i].t_id, NULL, routine_philo, &philo[i]) != 0)
			destroy_mutex(info, philo);
		i++;
	}
	if (info->nb_philo != 1)
		die_monitor(philo, info);
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
	return (1);
}

int	init_info(char **argv, char argc, t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].forks_r = &philo[(i + 1) % info->nb_philo].forks_l;
		if (argc == 6)
			philo[i].nb_eat = atoi(argv[5]);
		else
			philo[i].nb_eat = -1;
		i++;
	}
	return (1);
}

int	destroy_mutex(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].forks_l);
		pthread_mutex_destroy(philo[i].forks_r);
		pthread_mutex_destroy(&philo[i].time_lock);
		i++;
	}
	pthread_mutex_destroy(&info->eat_lock);
	pthread_mutex_destroy(&info->dead_lock);
	pthread_mutex_destroy(&info->print_lock);
	return (1);
}

int	init_all(char **argv, int argc, t_philo *philo, t_info *info)
{
	if (init_struct(argv, info) != 1)
    {
        //free(philo);
        return (0);
    }
	init_info(argv, argc, info, philo);
	if (init_mutex(info, philo) != 1)
	{
		free(philo);
		return (0);
	}
	if (init_thread(info, philo) != 1)
	{
		free(philo);
		return (0);
	}
	if (destroy_mutex(info, philo) != 1)
	{
		free(philo);
		return (0);
	}
	return (1);
}
