#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define USAGE_MSG "Usage: %s number_of_philosophers " \
					"time_to_die time_to_eat " \
					"time_to_sleep " \
					"[number_of_times_each_philosopher_must_eat]\n"

# define OK 0
# define ERR_PARAMS 1
# define ERR_ALLOC 2
# define ERR_NOT_UINT 3
# define ERR_MUTEX 4


typedef enum e_state
{
	ST_INVALID,
	ST_THINKING,
	ST_EATING,
	ST_SLEEPING,
	ST_DEAD
}	t_state;

typedef struct s_philo
{
	int				position;
	pthread_t		thread;
	t_state			state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	suseconds_t		last_meal_ts;
	suseconds_t		st_start_ts;
}	t_philo;

typedef struct s_params
{
	unsigned int	num_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_meals;
}	t_params;

// ft_checked_atoi.c
int	ft_checked_atou(const char *nptr, unsigned int *result);

#endif
