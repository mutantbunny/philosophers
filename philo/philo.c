/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:50:35 by gmachado          #+#    #+#             */
/*   Updated: 2023/01/17 04:14:14 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_params		params;

	if (save_args(&params, argc, argv) != OK)
	{
		printf(USAGE_MSG, argv[0]);
		return (ERR_PARAMS);
	}
	if (alloc_structs(&philos, &forks, params.num_philos))
		return(ERR_ALLOC);
	if (init_forks(params.num_philos, &forks))
		return (ERR_MUTEX);
	if (init_philos(params.num_philos, &philos, &forks))
		return (ERR_THREAD);
	check_philos();
}
