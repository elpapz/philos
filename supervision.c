/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:27:00 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/08 06:20:44 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"



void	join_n_destroy(t_args *args)
{
	int	i;

	i = 0;
	while (i > args->num_of_philos)
	{
		pthread_join(args->philo[i].threads, NULL);
		i++;
	}
	i = 0;
	while (i > args->num_of_philos)
	{
		pthread_mutex_destroy(&(args->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(args->check_died));
	pthread_mutex_destroy(&(args->dead_validation));
	pthread_mutex_destroy(&(args->eating));
	free(args->fork);
	free(args->philo);
	if (args->all_is_full == true)
		printf("ALL PHILOS ARE SATISFIED\n");
}

void	supervision_support(t_args *args, int i)
{
	if (args->philo[i].meals_eaten == args->must_eat_2_finish && args->philo[i].is_full == 0)
	{
		args->philo[i].is_full += 1;
		args->count_full_philos += 1;
	}
	if (args->count_full_philos == args->num_of_philos)
		args->all_is_full = true;
}

void	supervision(t_args *args)
{
	int	i;
	while (!args->all_is_full && !args->has_died)
	{
		i = -1;
		while (++i < args->num_of_philos)
		{
			pthread_mutex_lock(&args->check_died);
			if (time_window(get_time(), args->philo[i].last_meal) > args->time_2_die)
			{
				pthread_mutex_lock(&args->dead_validation);
				args->has_died = true;
				pthread_mutex_unlock(&args->dead_validation);
				printf("Time %ld | Philo %d has died\n", time_window(get_time(), args->time_win), args->philo[i].philo_id);
				pthread_mutex_unlock(&args->check_died);
				return ;
			}
		supervision_support(args, i);
		pthread_mutex_unlock(&args->check_died);
		}
	}
}