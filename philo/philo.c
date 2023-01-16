/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:50:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/17 00:56:03 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

static int	save_args(t_params *params, int argc, char *argv[]);

static int	init_forks(unsigned int num_philos, pthread_mutex_t **forks);

static int	init_philosophers(unsigned int num_philos, t_philo **philos,
				pthread_mutex_t **forks);

int	main(int argc, char *argv[])
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	unsigned int	i;
	t_params		params;

	if (save_args(&params, argc, argv) != OK)
	{
		printf(USAGE_MSG, argv[0]);
		return (ERR_PARAMS);
	}
	i = 0;
	philosophers = malloc( params.num_philos * sizeof(*philosophers));
	forks = malloc( params.num_philos * sizeof(*forks));
	if (philosophers == NULL || forks == NULL)
	{
		free(philosophers);
		free(forks);
		return(ERR_ALLOC);
	}
	if (init_forks(params.num_philos, &forks))
		return (ERR_MUTEX);

}

static int	save_args(t_params *params, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ERR_PARAMS);
	if (ft_checked_atou(argv[1], &params->num_philos))
		return (ERR_NOT_UINT);
	if (ft_checked_atou(argv[2], &params->time_to_die))
		return (ERR_NOT_UINT);
	if (ft_checked_atou(argv[3], &params->time_to_eat))
		return (ERR_NOT_UINT);
	if (ft_checked_atou(argv[4], &params->time_to_sleep))
		return (ERR_NOT_UINT);
	if (argc == 6)
	{
		if (ft_checked_atou(argv[5], &params->num_meals))
			return (ERR_NOT_UINT);
		return (OK);
	}
	params->num_meals = 0;
	return (OK);
}

static int	init_forks(unsigned int num_philos, pthread_mutex_t **forks)
{
	unsigned int	idx;

	idx = 0;
	while (idx < num_philos)
	{
		if (pthread_mutex_init(forks[idx], NULL))
			return (ERR_MUTEX);
		idx++;
	}
	return (OK);
}

static int	init_philosophers(unsigned int num_philos, t_philo **philos,
				pthread_mutex_t **forks)
{
	unsigned int	idx;

	idx = 0;
	while (idx < num_philos)
	{
		philos[idx]->position = idx;
		philos[idx]->state = ST_SLEEPING;
		philos[idx]->left_fork = forks[idx];
		philos[idx]->right_fork = forks[(idx + 1) % num_philos];
		philos[idx]->last_meal_ts;
		philos[idx]->st_start_ts;
		idx++;
	}
	return (OK);
}
