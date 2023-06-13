/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:29:55 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/13 06:18:46 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"


int	main(int ac, char **av)
{
	t_args	args;
	if ((ac != 5 && ac != 6) || check_input(av) == false)
	{
		printf("depois do check\n");
		return (error_message());
	}
	if (!init_args(&args, av))
	{
		printf("no init\n");
		return (error_message());
	}
	else
	{
		printf("The simulation has started\n");
		execute_philos(&args);
	}
	//destroy_n_clean(&args);
	//free(args.fork);
	//free(args.philo);
}