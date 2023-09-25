/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:49:31 by educlos           #+#    #+#             */
/*   Updated: 2023/09/25 20:34:26 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_struct(char **argv, t_info *info)
{
	if (ft_atoi(argv[1]) < 1)
        return (0);
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	info->die = 1;
	info->time_start = get_current_time();
	return (1);
}

int	check_arg(int ac, char **argv)
{
	int	i;
	int	y;

	i = 1;
	while (i < ac)
	{
		y = 0;
		while (argv[i][y] != '\0')
		{
			if (argv[i][y] < '0' || argv[i][y] > '9')
				return (0);
			y++;
		}
		i++;
	}
	return (1);
}

t_info	*get_info(void)
{
	static t_info	info;

	return (&info);
}

int	main(int argc, char **argv)
{
	int		i;
	t_philo	*philo;
	t_info	*info;

	i = 0;
	info = get_info();
	if (argc < 5 || argc > 6)
	{
		printf("Nombre d'arg incorrect");
		return (0);
	}
	if (check_arg(argc, argv) == 0)
	{
		printf("Argument faux");
		return (0);
	}
	philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!philo)
		return (0);
	init_all(argv, argc, philo, info);
	free(philo);
	return (1);
}
