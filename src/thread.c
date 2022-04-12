/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:34:21 by gshim             #+#    #+#             */
/*   Updated: 2022/04/12 16:52:08 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	get_thread_phase(t_personal_info *th)
{
	struct timeval time;
	int timestamp;

	printf(">>%.2f second\n", (float)relative_time(th->info->start)/1000000);
	(void)th;
	if (timestamp % (th->info->phil_eat_time * 3) < th->info->phil_eat_time)
		return (1);
	else if (timestamp % (th->info->phil_eat_time * 3) < th->info->phil_eat_time * 2)
		return (2);
	else if (timestamp % (th->info->phil_eat_time * 3) < th->info->phil_eat_time * 3)
		return (3);
	else
		return (-1);
}

void thread_pick(t_personal_info *d)
{
	printf("timestamp_in_ms %d has taken a fork\n", d->idx);
}

void thread_eat(t_personal_info *d)
{
	// 포크 2개를 집는다.
	thread_pick(d);
	thread_pick(d);

	// 먹는다.
	printf("timestamp_in_ms %d is eating\n", d->idx);
	usleep(d->info->phil_eat_time * 1000);

	d->last_eat = get_time();
}

void thread_sleep(t_personal_info *d)
{
	printf("timestamp_in_ms %d is sleeping\n", d->idx);
	usleep(d->info->phil_slp_time * 1000);
}

void thread_think(t_personal_info *d)
{
	printf("timestamp_in_ms %d is thinking\n", d->idx);
	while(1)
	{
		// 쓰레드의 그룹이 식사할 권한을 얻는다면 break.
		if (d->groupnum)	// 미완성..
			break;
	}
}

void thread_A(t_personal_info *d)
{
	(void)d;
	int phase;

	phase = get_thread_phase(d);
	printf("phase : %d\n", phase);
	// 1페이즈 : 먹기
	if (phase == 1)
		thread_eat(d);
	// 2페이즈 : 잠자기
	else if(phase == 2)
		thread_sleep(d);
	// 3페이즈 : 생각하기
	else if(phase == 3)
		thread_think(d);

	return ;
}

bool	thread_survive(t_personal_info *d)
{
	size_t starve_time;

	get_time();
	return (d->last_eat - get_time() < d->info->phil_life);
}

// 죽는걸 어디서 검사해야 하지..?
void thread_AA(t_personal_info *d)
{
	// 생존체크.
	if (!thread_survive(d))
	{
		printf("%.2f_in_ms %d died", (float)relative_time(d->info->start)/1000000, d->idx);
		return ;
	}

	// 현재 쓰레드의 그룹 권한으로 먹을 수 있다면
		// 2개의 포크를 쥔다.
		// EAT
		// 곧바로 이어서, SLEEP

	// 먹을 수 없다면 THINK하며 기다림.
}
