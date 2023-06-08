/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 05:20:02 by acanelas          #+#    #+#             */
/*   Updated: 2023/05/31 19:56:56 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

suseconds_t	get_time(void)
{
	struct timeval	time_ms;

	gettimeofday(&time_ms, NULL);
	return((time_ms.tv_sec * 1000) + (time_ms.tv_usec / 1000));
}

suseconds_t	time_window(int curr, int prev)
{
	return (curr - prev);
}
