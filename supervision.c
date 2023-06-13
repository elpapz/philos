/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 02:27:00 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/13 06:16:49 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	destroy_n_clean(t_args *args)
{
	int i;

	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_mutex_destroy(&args->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&(args->print));
	pthread_mutex_destroy(&(args->check));
	pthread_mutex_destroy(&(args->check_die));
	//pthread_mutex_destroy(&(args->actions));
	//pthread_mutex_destroy(&args->supervisor);
	free(args->fork);
	free(args->philo);
	if (args->all_is_full == true)
		printf("ALL PHILOS ARE SATISFIED\n");
}

bool	supervision_support(t_args *args, int i)
{
	//pthread_mutex_lock(&args->supervisor);
	if (args->philo[i].meals_eaten == args->must_eat_2_finish && args->philo[i].is_full == 0)
	{
		//pthread_mutex_unlock(&args->check_died);
		args->philo[i].is_full += 1;
		args->count_full_philos += 1;
		//pthread_mutex_unlock(&args->supervisor);
	}
	if (args->count_full_philos == args->num_of_philos)
	{
		//pthread_mutex_lock(&args->check_died);
		args->all_is_full = true;
		//pthread_mutex_unlock(&args->supervisor);
		return (false);
	}
	//pthread_mutex_unlock(&args->supervisor);
	return (true);
}
/*
void	dead_print(suseconds_t time, t_args *args)
{
	if (args->has_died == true)
		printf("Time %ld | Philo %d has died\n", time, args->philo->philo_id);
}
*/
void	supervision(t_args *args)
{
	int	i;
	//pthread_mutex_lock(&args->check_died);
	while (!args->all_is_full && !args->has_died)
	{
		//pthread_mutex_lock(&args->check_died);
		i = -1;
		while (++i < args->num_of_philos)
		{
			pthread_mutex_lock(&args->check_die);
			if (time_window(get_time(), args->philo[i].last_meal) > args->time_2_die || args->has_died)
			{
				pthread_mutex_lock(&args->check);
				args->has_died = true;
				pthread_mutex_unlock(&args->check);
				//dead_print(time_window(get_time(), args->time_win), args);
				printf("Time %ld | Philo %d has died\n", time_window(get_time(), args->time_win), args->philo[i].philo_id);
				pthread_mutex_unlock(&args->check_die);
				return ;
			}
			if (supervision_support(args, i) == false)
			{
				pthread_mutex_unlock(&args->check_die);
				break ;
			}
		pthread_mutex_unlock(&args->check_die);
		}
	//pthread_mutex_unlock(&args->check_died);
	}
	//pthread_mutex_unlock(&args->check_died);
	//pthread_mutex_destroy(&args->supervisor);
}
