/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:02:57 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/13 06:17:34 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	deal_with_one(suseconds_t time, t_philos *philo)
{
	//pthread_mutex_lock(&philo->args->check_die);
	if (philo->args->num_of_philos == 1)
	{
		//pthread_mutex_lock(&philo->args->check_die);
		printf("Time %ld | Philo %d has taken a fork\n", time, philo->philo_id);
		usleep(philo->args->time_2_die * 1000);
		pthread_mutex_lock(&philo->args->check);
		philo->args->has_died = true;
		pthread_mutex_unlock(&philo->args->check);
	}
}

bool	philo_is_eating(t_philos *philo)
{
	//t_args	*args;
	//args = philo->args;

	pthread_mutex_lock(&(philo->args->fork[philo->lfork]));
	//pthread_mutex_lock(&philo->args->print);
	if (philo->args->num_of_philos == 1)
	{

		//pthread_mutex_lock(&philo->args->check_die);
		deal_with_one(time_window(get_time(), philo->args->time_win), philo);
		//pthread_mutex_unlock(&philo->args->print);
		//pthread_mutex_unlock(&philo->args->check_die);
		pthread_mutex_unlock(&(philo->args->fork[philo->lfork]));
		return(false);
	}
	pthread_mutex_lock(&(philo->args->fork[philo->rfork]));
	print_eating(time_window(get_time(), philo->args->time_win), philo);
	pthread_mutex_lock(&philo->args->check_die);
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->args->check_die);
	usleep(philo->args->time_2_eat * 1000);
	pthread_mutex_unlock(&(philo->args->fork[philo->lfork]));
	pthread_mutex_unlock(&(philo->args->fork[philo->rfork]));
	return (true);
}

void	*routine(void *args)
{
	t_philos	*philo;
	//t_args		*arg;

	philo = (t_philos*)args;
	//arg = philo->args;
	while (1)
	{
		pthread_mutex_lock(&philo->args->check_die);
		if (!philo->args->has_died && !philo->is_full && !philo->args->all_is_full)
		{
			pthread_mutex_unlock(&philo->args->check_die);
			if (!philo_is_eating(philo))
			{
				break;
			}
			go_to_sleep(time_window(get_time(), philo->args->time_win), philo);
			go_to_think(time_window(get_time(), philo->args->time_win), philo);
		}
		else
		{
			pthread_mutex_unlock(&philo->args->check_die);
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
	//usleep(args->time_2_die * 500);
	i = 0;
	while (i < args->num_of_philos)
	{
		pthread_join(args->philo[i].threads, NULL);
		i++;
	}
	destroy_n_clean(args);
}
