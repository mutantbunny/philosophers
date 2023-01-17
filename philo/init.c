/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:36:59 by gmachado          #+#    #+#             */
/*   Updated: 2023/01/17 04:14:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	save_args(t_params *params, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ERR_PARAMS);
	if (checked_atou(argv[1], &params->num_philos))
		return (ERR_NOT_UINT);
	if (checked_atou(argv[2], &params->time_to_die))
		return (ERR_NOT_UINT);
	if (checked_atou(argv[3], &params->time_to_eat))
		return (ERR_NOT_UINT);
	if (checked_atou(argv[4], &params->time_to_sleep))
		return (ERR_NOT_UINT);
	if (argc == 6)
	{
		if (checked_atou(argv[5], &params->num_meals))
			return (ERR_NOT_UINT);
		return (OK);
	}
	params->num_meals = 0;
	return (OK);
}

int	alloc_structs(t_philo **philos, pthread_mutex_t **forks, unsigned int np)
{
	*philos = malloc(np * sizeof(**philos));
	*forks = malloc(np * sizeof(**forks));
	if (philos == NULL || forks == NULL)
	{
		free(*philos);
		free(*forks);
		return(ERR_ALLOC);
	}
	return(OK);
}

int	init_forks(unsigned int num_philos, pthread_mutex_t **forks)
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

int	init_philos(unsigned int num_philos, t_philo **philos,
				pthread_mutex_t **forks)
{
	unsigned int	idx;
	const

	idx = 0;
	while (idx < num_philos)
	{
		philos[idx]->position = idx;
		philos[idx]->state = ST_NO_FORK;
		philos[idx]->left_fork = forks[idx];
		philos[idx]->right_fork = forks[(idx + 1) % num_philos];
		if (pthread_create(&(philos[idx]->thread), NULL,
			philo_handler, philos[idx]))
			return (ERR_THREAD);
		idx++;
	}
	return (OK);
}
