/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:50:35 by gmachado          #+#    #+#             */
/*   Updated: 2023/02/08 03:35:00 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_fork		*forks;
	t_params	params;
	t_error		err;

	if (save_args(&params, argc, argv) != OK)
	{
		printf(USAGE_MSG, argv[0]);
		return (ERR_PARAMS);
	}
	philos = NULL;
	forks = NULL;
	err = init_forks(params.num_philos, &forks);
	if (err)
		return (handle_error(err, philos, forks));
	err = init_philos(params.num_philos, &philos, &forks);
	if (err)
		return (handle_error(err, philos, forks));
	for (unsigned i = 0; i < params.num_philos; ++i)
		pthread_join(philos[i].thread, NULL);
	cleanup(philos, forks);
}
