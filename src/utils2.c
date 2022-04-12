/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:21:30 by gshim             #+#    #+#             */
/*   Updated: 2022/04/12 14:56:55 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	get_time()
{
	struct timeval current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec);
}

size_t	relative_time(size_t start)
{
	struct timeval current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - start);
}
