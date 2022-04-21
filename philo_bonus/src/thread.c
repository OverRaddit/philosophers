/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:34:21 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 16:16:28 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	thread_pick(t_personal_info *d)
{
	sem_wait(d->fork);
	logging(GRAB, d->idx, d->print);

	sem_wait(d->fork);
	logging(GRAB, d->idx, d->print);
}

void	thread_eat(t_personal_info *d)
{
	logging(EAT, d->idx, d->print);
	gsleep(d->info->phil_eat_time * 1000);
	sem_post(d->fork);
	sem_post(d->fork);
	d->eat_count += 1;
	d->last_eat = get_time();
}

void	thread_sleep(t_personal_info *d)
{
	logging(SLEEP, d->idx, d->print);
	gsleep(d->info->phil_slp_time * 1000);
}

void	thread_think(t_personal_info *d)
{
	logging(THINK, d->idx, d->print);
}

void	*t_function(void *pinfo)
{
	t_personal_info	*d;

	d = (t_personal_info *)pinfo;

	// 세마포어 집기
	sem_wait(d->die);
	sem_wait(d->full);

	if (d->idx % 2 == 1)
		gsleep(50);
	while (1)
	{
		thread_pick(d);
		thread_eat(d);
		thread_sleep(d);
		gsleep(500);
		thread_think(d);
	}
	return (0);
}
