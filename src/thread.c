/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:34:21 by gshim             #+#    #+#             */
/*   Updated: 2022/04/18 22:10:36 by gshim            ###   ########.fr       */
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

	pthread_mutex_lock(&(d->data->fork[first % d->info->phil_num]));
	logging(GRAB, d->idx);

	pthread_mutex_lock(&(d->data->fork[second % d->info->phil_num]));
	logging(GRAB, d->idx);
}

void thread_eat(t_personal_info *d)
{
	// ===============critical section ======================
		// 먹는다.
		logging(EAT, d->idx);
		gsleep(d->info->phil_eat_time * 1000);
	// ===============critical section ======================
	pthread_mutex_unlock(&(d->data.fork[d->idx % d->info->phil_num]));
	pthread_mutex_unlock(&(d->data.fork[(d->idx + 1) % d->info->phil_num]));

	// 다 먹고나서부터 다시 시간측정.
	d->eat_count += 1;
	d->last_eat = get_time();
}

void thread_sleep(t_personal_info *d)
{
	logging(SLEEP, d->idx);
	gsleep(d->info->phil_slp_time * 1000);
}

void thread_think(t_personal_info *d)
{
	logging(THINK, d->idx);
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
