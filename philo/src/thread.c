/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:34:21 by gshim             #+#    #+#             */
/*   Updated: 2022/04/24 13:08:37 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	thread_pick(t_personal_info *d)
{
	if (d->idx % 2 == 0)
	{
		pthread_mutex_lock(d->r);
		logging(GRAB, d->idx, d->printer);
		pthread_mutex_lock(d->l);
		logging(GRAB, d->idx, d->printer);
	}
	else
	{
		pthread_mutex_lock(d->l);
		logging(GRAB, d->idx, d->printer);
		pthread_mutex_lock(d->r);
		logging(GRAB, d->idx, d->printer);
	}
}

void	thread_eat(t_personal_info *d)
{
	logging(EAT, d->idx, d->printer);
	gsleep(d->info->phil_eat_time * 1000);
	pthread_mutex_unlock(d->r);
	pthread_mutex_unlock(d->l);
	d->eat_count += 1;
	d->last_eat = get_time();
}

void	thread_sleep(t_personal_info *d)
{
	logging(SLEEP, d->idx, d->printer);
	gsleep(d->info->phil_slp_time * 1000);
}

void	thread_think(t_personal_info *d)
{
	logging(THINK, d->idx, d->printer);
}

void	*t_function(void *pinfo)
{
	t_personal_info	*d;

	d = (t_personal_info *)pinfo;
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
