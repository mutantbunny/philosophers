/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:50:38 by gmachado          #+#    #+#             */
/*   Updated: 2023/07/06 06:28:43 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <bits/pthreadtypes.h>

# define SLEEP_TIME_STEP 100
# define CHECK_WAIT_TIME 2
# define THINK_TIME 1

typedef pthread_mutex_t	t_fork;
typedef struct s_params	t_params;
typedef struct s_philo	t_philo;

typedef enum e_error
{
	OK,
	ERR_PARAMS,
	ERR_ALLOC,
	ERR_MUTEX,
	ERR_THREAD
}	t_error;

typedef enum e_state
{
	ST_THINKING,
	ST_GOT_FORK,
	ST_EATING,
	ST_SLEEPING,
	ST_DEAD
}	t_state;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				num_must_eat;
	t_bool			dinner_over;
	long long		start_ts;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		check_death_thread;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	dinner_over_mtx;
	pthread_mutex_t	must_eat_mtx;
};

struct s_philo
{
	int				number;
	int				remaining_meals;
	long long		last_meal_ts;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_params		*pars;
	pthread_t		thread;
	pthread_mutex_t	meal_mtx;
};

// checker_thread.c
void		*check_death_handler(void *arg);

// cleanup.c
t_error		cleanup(t_params *pars);
t_error		handle_error(t_params *pars, t_error err);

// ft_atoi.c
t_error		checked_atoi(const char *nptr, int *result);

// init.c
t_error		get_args(t_params *pars, int argc, char **argv);
t_error		init_forks(int num_forks, t_fork **forks);
t_error		init_parameters(t_params *pars);
t_error		init_philos(t_params *pars);

// mutex_ops.c
void		end_dinner(t_params *pars);
t_bool		get_dinner_over(t_params *pars);
long long	get_last_meal_timestamp(t_philo *philo);
void		set_last_meal_timestamp(t_philo *philo);

// philo_thread.c
void		*philo_handler(void *arg);

// time.c
void		sleep_in_ms(long long sleep_time);
long long	timestamp_in_ms(void);

// utils.c
t_fork		*first_fork(t_philo *philo);
void		print_state(t_params *pars, int idx, t_state state);
t_fork		*second_fork(t_philo *philo);

#endif
