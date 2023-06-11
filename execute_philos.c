/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:02:57 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/09 04:26:23 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	deal_with_one(suseconds_t time, t_philos *philo)
{
	if (philo->args->num_of_philos == 1)
	{
		printf("Time %ld | Philo %d has taken a fork\n", time, philo->philo_id);
		usleep(philo->args->time_2_die * 1000);
		philo->args->has_died = true;
	}
}

bool	philo_is_eating(t_philos *philo)
{
	t_args	*args;
	args = philo->args;

	pthread_mutex_lock(&(args->fork[philo->lfork]));
	if (philo->args->num_of_philos == 1)
	{
		deal_with_one(time_window(get_time(), args->time_win), philo);
		pthread_mutex_unlock(&(args->fork[philo->lfork]));
		return(false);
	}
	pthread_mutex_lock(&(args->fork[philo->rfork]));
	print_eating(time_window(get_time(), args->time_win), philo);
	pthread_mutex_lock(&args->eating);
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&args->eating);
	usleep(philo->args->time_2_eat * 1000);
	pthread_mutex_unlock(&args->fork[philo->lfork]);
	pthread_mutex_unlock(&args->fork[philo->rfork]);
	return (true);
}

void	*routine(void *args)
{
	t_philos	*philo;
	t_args		*arg;

	philo = (t_philos*)args;
	arg = philo->args;
	while (1)
	{
		pthread_mutex_lock(&arg->check_died);
		if (!arg->has_died && !philo->is_full && !arg->all_is_full)
		{
			pthread_mutex_unlock(&arg->check_died);
			if (!philo_is_eating(philo))
				break;
			go_to_sleep(time_window(get_time(), arg->time_win), philo);
			go_to_think(time_window(get_time(), arg->time_win), philo);
		}
		else
		{
			pthread_mutex_unlock(&arg->check_died);
			break;
		}
	}
	return (NULL);
}

void	execute_philos(t_args *args)
{
	int	i;
	args->time_win = get_time();
	i = -1;
	while (++i < args->num_of_philos)
		pthread_create(&args->philo[i].threads, NULL, &routine, &args->philo[i]);
	supervision(args);
	usleep(args->time_2_die * 500);
	i = 0;
	while (i > args->num_of_philos)
	{
		pthread_join(args->philo[i].threads, NULL);
		i++;
	}
	if (args->all_is_full == true)
		printf("ALL THE PHILOS ARE SATISFIED\n");
	destroy_n_clean(args);
}