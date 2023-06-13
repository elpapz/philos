/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 06:07:46 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/13 00:59:24 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	error_message()
{
	printf("Must have at least 5 args\n");
	printf("The args must be only composed by numbers\n");
	printf("The number of Philos must be bigger than 0 and smaller then 200\n");
	printf("All the args refering to time must be bigger then 60\n");
	printf("\n\n");
	printf("PLEASE TRY AGAIN, FOLLOWING THE RULES ABOVE... :)\n");
	return (EXIT_FAILURE);
}

void	print_eating(suseconds_t time, t_philos *philo)
{
	pthread_mutex_lock(&philo->args->check_die);
	if (!philo->args->has_died && !philo->args->all_is_full)
	{
		printf("Time %ld | Philo %d has taken a fork\n", time, philo->philo_id);
		printf("Time %ld | Philo %d has taken a fork\n", time, philo->philo_id);
		printf("Time %ld | Philo %d is eating \n", time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->check_die);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->check_die);
		return ;
	}
}

void	go_to_sleep(suseconds_t time, t_philos *philo)
{
	pthread_mutex_lock(&philo->args->check_die);
	if (!philo->args->has_died && !philo->args->all_is_full)
	{
		printf("Time %ld | Philo %d is sleeping\n", time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->check_die);
		usleep(philo->args->time_2_sleep * 1000);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->check_die);
		return ;
	}
}

void	go_to_think(suseconds_t time, t_philos *philo)
{
	pthread_mutex_lock(&philo->args->check_die);
	if (!philo->args->has_died && !philo->args->all_is_full)
	{
		printf("Time %ld | Philo %d is thinking\n", time, philo->philo_id);
		pthread_mutex_unlock(&philo->args->check_die);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->check_die);
		return ;
	}
}
