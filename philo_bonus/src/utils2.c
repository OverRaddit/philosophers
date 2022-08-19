/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:21:30 by gshim             #+#    #+#             */
/*   Updated: 2022/08/19 18:57:04 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec);
}

size_t	relative_time(size_t start)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - start);
}

void	gsleep(size_t usec)
{
	size_t	start;

	start = get_time();
	// usleep
	if (usec >= 5 * 1000)
		usleep(usec - 5 * 1000);
	while (1)
	{
		if (relative_time(start) >= usec)
			break ;
		usleep(50);
	}
}
