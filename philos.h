/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acanelas <acanelas@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:34:04 by acanelas          #+#    #+#             */
/*   Updated: 2023/06/17 05:26:01 by acanelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_args
{
	int					num_of_philos;
	int					time_2_die;
	int					time_2_eat;
	int					time_2_sleep;
	int					must_eat_2_finish;
	int					count_full_philos;
	bool				all_is_full;
	bool				has_died;
	suseconds_t			time_win;
	pthread_mutex_t		check_status;
	pthread_mutex_t		dead;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	struct s_philos		*philo;
}						t_args;

typedef struct s_philos
{
	t_args		*args;
	pthread_t	threads;
	suseconds_t	last_meal;
	int			philo_id;
	int			meals_eaten;
	int			is_full;
	int			lfork;
	int			rfork;
}				t_philos;

int			ft_atoi(char *str);
bool		ft_isdigit(char *str);
bool		check_input(char **av);
suseconds_t	get_time(void);
suseconds_t	time_window(int curr, int prev);
bool		creat_forks(t_args *args);
bool		init_args(t_args *args, char **av);
void		execute_philos(t_args *args);
void		deal_with_one(suseconds_t time, t_philos *philo);
void		go_to_think(suseconds_t time, t_philos *philo);
void		go_to_sleep(suseconds_t time, t_philos *philo);
void		print_eating(suseconds_t time, t_philos *philo);
void		supervision(t_args *args);
void		destroy_n_clean(t_args *args);
int			error_message(void);

#endif