/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:27:00 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/09 05:15:04 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	destroy_n_clean(t_args *args)
{
	int i;
	
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
	//pthread_mutex_lock(&args->check_died);
	if (args->philo[i].meals_eaten == args->must_eat_2_finish && args->philo[i].is_full == 0)
	{
		//pthread_mutex_unlock(&args->check_died);
		args->philo[i].is_full += 1;
		args->count_full_philos += 1;
		//pthread_mutex_unlock(&args->check_died);
	}
	if (args->count_full_philos == args->num_of_philos)
	{
		//pthread_mutex_lock(&args->check_died);
		args->all_is_full = true;
		//pthread_mutex_unlock(&args->check_died);
	}
}

void	supervision(t_args *args)
{
	int	i;
	//pthread_mutex_lock(&args->check_died);
	while (!args->all_is_full && !args->has_died)
	{
		i = -1;
		while (++i < args->num_of_philos)
		{
			pthread_mutex_lock(&args->supervisor);
			if (time_window(get_time(), args->philo[i].last_meal) > args->time_2_die || args->has_died)
			{
				pthread_mutex_lock(&args->dead_validation);
				args->has_died = true;
				pthread_mutex_unlock(&args->dead_validation);
				printf("Time %ld | Philo %d has died\n", time_window(get_time(), args->time_win), args->philo[i].philo_id);
				pthread_mutex_unlock(&args->supervisor);
				return ;
			}
		supervision_support(args, i);
		pthread_mutex_unlock(&args->supervisor);
		}
	}
	//pthread_mutex_unlock(&args->check_died);
	pthread_mutex_destroy(&args->supervisor);
}
