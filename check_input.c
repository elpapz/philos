/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:30:40 by acanelas          #+#    #+#             */
/*   Updated: 2023/05/31 20:12:16 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	ft_atoi(char *str)
{
	int		s;
	int		r;
	int		a;

	a = 0;
	r = 0;
	s = 1;
	while ((str[a] >= 9 && str[a] <= 13) || (str[a] == 32))
	a++;
	if (str[a] == '-')
	{
		s = -1;
		a++;
	}
	else if (str[a] == '+')
	a++;
	while (str[a] && str[a] >= '0' && str[a] <= '9')
	{
		r = r * 10 + (str[a] - '0');
		a++;
	}
	return (r * s);
}

bool	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
		}
		else
			return (false);
	}
return (true);
}

bool	check_input(char **av)
{
	int	i;
	
	i = 1;
	while (av[i])
	{
		if (ft_isdigit(av[i]) == false)
			return (false);
		i++;
	}
	i = 2;
	while (av[i])
	{
		if (ft_atoi(av[i]) < 60)
			return (false);
		i++;
	}
	if (ft_atoi(av[1]) == 0 || ft_atoi(av[1]) > 200)
		return (false);
	if (av[5] && ft_atoi(av[5]) == 0)
		return (false);
	return (true);
}