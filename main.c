/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:29:55 by acanelas          #+#    #+#             */
/*   Updated: 2023/08/02 22:24:56 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	main(int ac, char **av)
{
	t_args	args;

	if ((ac != 5 && ac != 6) || check_input(av) == false)
	{
		return (error_message());
	}
	if (!init_args(&args, av))
	{
		return (error_message());
	}
	else
	{
		printf("The simulation has started\n");
		execute_philos(&args);
	}
}
