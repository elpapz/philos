/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:27:26 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/08 05:42:03 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static bool	creat_forks(t_args *args)
{
	int	i;

	i = 0;
	args->fork = malloc(sizeof(pthread_mutex_t) * args->num_of_philos);
	if (!args->fork)
		return(false);
	while (args->num_of_philos > i)
	{
		if (pthread_mutex_init(&args->fork[i], NULL))
			return (false);
		i++;
	}
	if (pthread_mutex_init(&args->check_died, NULL))
		return (false);
	if (pthread_mutex_init(&args->dead_validation, NULL))
		return (false);
	if (pthread_mutex_init(&args->eating, NULL))
		return (false);
	return (true);
}

static bool	sit_philos(t_args *args)
{
	int	i;

	i = 0;
	args->philo = malloc(sizeof(t_philos) * args->num_of_philos);
	if (!args->philo)
		return (false);
	while (i < args->num_of_philos)
	{
		args->philo[i].philo_id = i + 1;
		args->philo[i].meals_eaten = 0;
		args->philo[i].args = args;
		args->philo[i].is_full = 0;
		if (args->num_of_philos > 1 && i != (args->num_of_philos -1))
		{
			args->philo[i].lfork = i;
			args->philo[i].rfork = i + 1;
		}
		else if (args->num_of_philos > 1 && i == (args->num_of_philos -1))
		{
			args->philo[i].lfork = 0;
			args->philo[i].rfork = i;
		}
	i++;
	}
return (true);
}

bool	init_args(t_args *args, char **av)
{
	args->num_of_philos = ft_atoi(av[1]);
	args->time_2_die = ft_atoi(av[2]);
	args->time_2_eat = ft_atoi(av[3]);
	args->time_2_sleep = ft_atoi(av[4]);
	if (av[5])
		args->must_eat_2_finish = ft_atoi(av[5]);
	else
		args->must_eat_2_finish = -1;
	args->all_is_full = false;
	args->has_died = 0;
	args->count_full_philos = 0;
	if (creat_forks(args) == false || sit_philos(args) == false)
		return (false);
	return (true);
}
