/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 01:36:59 by gmachado          #+#    #+#             */
/*   Updated: 2023/02/08 03:32:42 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error	save_args(t_params *params, int argc, char *argv[])
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

t_error	init_forks(unsigned int num_forks, t_fork **forks)
{
	unsigned int	idx;

	*forks = malloc(num_forks * sizeof(**forks));
	if (*forks == NULL)
		return(ERR_ALLOC);
	idx = 0;
	while (idx < num_forks)
	{
		if (pthread_mutex_init(&((*forks)[idx].mutex), NULL))
			return (ERR_MUTEX);
		(*forks)[idx].taken = FALSE;
		idx++;
	}
	return (OK);
}

t_error	init_philos(unsigned int num_philos, t_philo **philos,
				t_fork **forks)
{
	unsigned int	idx;

	*philos = malloc(num_philos * sizeof(**philos));
	if (philos == NULL)
		return(ERR_ALLOC);
	idx = 0;
	while (idx < num_philos)
	{
		(*philos)[idx].position = idx;
		(*philos)[idx].state = ST_NO_FORK;
		(*philos)[idx].left_fork = &((*forks)[idx]);
		(*philos)[idx].right_fork = &((*forks)[(idx + 1) % num_philos]);
		if (pthread_create(&((*philos)[idx].thread), NULL,
			philo_handler, &(*philos)[idx]))
			return (ERR_THREAD);
		idx++;
	}
	return (OK);
}
