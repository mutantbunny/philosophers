/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:41:40 by gmachado          #+#    #+#             */
/*   Updated: 2023/02/08 03:13:58 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <bits/pthreadtypes.h>

# define USAGE_MSG "Usage: %s number_of_philosophers " \
					"time_to_die time_to_eat " \
					"time_to_sleep " \
					"[number_of_times_each_philosopher_must_eat]\n"

typedef enum e_error
{
	OK,
	ERR_PARAMS,
	ERR_ALLOC,
	ERR_NOT_UINT,
	ERR_MUTEX,
	ERR_THREAD
}	t_error;

typedef enum e_state
{
	ST_INVALID,
	ST_THINKING,
	ST_NO_FORK,
	ST_ONE_FORK,
	ST_EATING,
	ST_SLEEPING,
	ST_DEAD
}	t_state;

typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	t_bool			taken;
} t_fork;

typedef struct s_philo
{
	int			position;
	pthread_t	thread;
	t_state		state;
	t_fork		*left_fork;
	t_fork		*right_fork;
	suseconds_t	last_meal_ts;
	suseconds_t	st_start_ts;
}	t_philo;

typedef struct s_params
{
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_meals;
}	t_params;

// checked_atoi.c
t_error	checked_atou(const char *nptr, unsigned int *result);

//cleanup.c
void	cleanup(t_philo *philos, t_fork *forks);
t_error	handle_error(t_error err, t_philo *philos, t_fork *forks);

// init.c
t_error	save_args(t_params *params, int argc, char *argv[]);
t_error	init_forks(unsigned int num_philos, t_fork **forks);
t_error	init_philos(unsigned int num_philos, t_philo **philos,
					t_fork **forks);

// states.c
void	*philo_handler(void *arg);

#endif
