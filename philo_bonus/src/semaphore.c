/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 11:02:23 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 12:20:23 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	semaphore(sem_t **sem, char *filename, size_t size)
{
	sem_unlink(filename);
	*sem = sem_open(filename, O_CREAT, 0644, size);	// 왜 0644?
	if (*sem == SEM_FAILED)
		return (true);
}
