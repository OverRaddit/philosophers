/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:34:21 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 15:34:14 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void thread_pick(t_personal_info *d)
{
	int		first;
	int		second;

	// 짝수(i)는 오른쪽(i)부터, 홀수(i)는 왼쪽(i+1)부터 잡는다.
	// 짝수면 first가 i가되고 홀수면 first가 i+1이됨.
	first = d->idx + (d->idx % 2 != 0);
	second = d->idx + (d->idx % 2 == 0);

	// 철학자는 data를 접근하지 않고 l,r에 있는 포크에만 접근한다.
	// 홀짝 구분에 따른 좌우구분이 필요한데..
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

void thread_eat(t_personal_info *d)
{
	// ===============critical section ======================
		// 먹는다.
		logging(EAT, d->idx, d->printer);
		gsleep(d->info->phil_eat_time * 1000);
	// ===============critical section ======================
	pthread_mutex_unlock(d->r);
	pthread_mutex_unlock(d->l);

	// 다 먹고나서부터 다시 시간측정.
	d->eat_count += 1;
	d->last_eat = get_time();
}

void thread_sleep(t_personal_info *d)
{
	logging(SLEEP, d->idx, d->printer);
	gsleep(d->info->phil_slp_time * 1000);
}

void thread_think(t_personal_info *d)
{
	logging(THINK, d->idx, d->printer);
}

void thread_AA(t_personal_info *d)
{
	// 홀짝 구분을 위한 시간차.
	if (d->idx % 2 == 1)
		gsleep(50);	// 0.00005초 지연시키기.
	while(1)
	{
		thread_pick(d);
		thread_eat(d);
		thread_sleep(d);
		gsleep(50);
		thread_think(d);
	}
}
