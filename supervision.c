/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:27:00 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/17 04:58:01 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	destroy_n_clean(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&args->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&(args->print));
	pthread_mutex_destroy(&(args->dead));
	pthread_mutex_destroy(&(args->check_status));
	free(args->fork);
	free(args->philo);
	if (args->all_is_full == true)
		printf("ALL PHILOS ARE SATISFIED\n");
}

bool	supervision_support(t_args *args, int i)
{
	if (args->philo[i].meals_eaten == args->must_eat_2_finish
		&&args->philo[i].is_full == 0)
	{
		args->philo[i].is_full += 1;
		args->count_full_philos += 1;
	}
	if (args->count_full_philos == args->num_of_philos)
	{
		args->all_is_full = true;
		pthread_mutex_unlock(&args->check_status);
		return (false);
	}
	pthread_mutex_unlock(&args->check_status);
	return (true);
}

void	sad_news(suseconds_t time, t_args *args)
{
	printf("Time %ld | Philo %d has died\n", time, args->philo->philo_id);
}

void	supervision(t_args *args)
{
	int	i;

	while (!args->all_is_full && !args->has_died)
	{
		i = -1;
		while (++i < args->num_of_philos)
		{
			pthread_mutex_lock(&args->check_status);
			if (time_window(get_time(), args->philo[i].last_meal)
				> args->time_2_die || args->has_died)
			{
				pthread_mutex_lock(&args->dead);
				args->has_died = true;
				pthread_mutex_unlock(&args->dead);
				sad_news(time_window(get_time(), args->time_win), args);
				pthread_mutex_unlock(&args->check_status);
				return ;
			}
			if (supervision_support(args, i) == false)
				break ;
		}
	}
}
