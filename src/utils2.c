/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:21:30 by gshim             #+#    #+#             */
/*   Updated: 2022/04/17 17:52:23 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// 초 단위로 동작
// =>
// ms 단위로 동작

size_t	get_time()
{
	struct timeval current;

	gettimeofday(&current, 0);
	//return (current.tv_sec * 1000 * 1000 + current.tv_usec)/1000;
	return (current.tv_sec * 1000 * 1000 + current.tv_usec);
}

size_t	relative_time(size_t start)
{
	struct timeval current;

	gettimeofday(&current, 0);
	//return (current.tv_sec * 1000 * 1000 + current.tv_usec - start)/1000;
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - start);
}
