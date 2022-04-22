/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:02:23 by gshim             #+#    #+#             */
/*   Updated: 2022/04/22 21:33:56 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	semaphore(sem_t **sem, char *filename, size_t size)
{
	sem_unlink(filename);
	*sem = sem_open(filename, O_CREAT, 0644, size);
	if (*sem == SEM_FAILED)
		return (false);
	return (true);
}
