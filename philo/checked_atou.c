/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checked_atou.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:55:11 by gmachado          #+#    #+#             */
/*   Updated: 2023/01/17 01:45:56 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	get_next_positive_digit(unsigned int result,
						char ch, int *invalid);

static int	ft_isspace(char c);

int	ft_checked_atou(const char *nptr, unsigned int *result)
{
	int	invalid;

	*result = 0;
	invalid = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		return (ERR_NOT_UINT);
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && invalid == 0)
		*result = (get_next_positive_digit(*result, *nptr++, &invalid));
	if (invalid || *nptr != '\0')
	{
		*result = 0;
		return (ERR_NOT_UINT);
	}
	return (OK);
}

static unsigned int	get_next_positive_digit(unsigned int result,
						char ch, int *invalid)
{
	unsigned int	new_result;

	*invalid = 0;
	new_result = 10 * result + (unsigned int)(ch - '0');
	if (new_result < result)
		*invalid = 1;
	return (new_result);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
