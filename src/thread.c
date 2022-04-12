/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:34:21 by gshim             #+#    #+#             */
/*   Updated: 2022/04/12 22:36:41 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	get_thread_phase(t_personal_info *th)
{
	struct timeval time;
	int timestamp;

	//printf(">>2f second\n", (float)relative_time(th->info->start)/1000000);
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
	pthread_mutex_lock(&(data.fork[d->idx % d->info->phil_num]));
	d->l = &(data.fork[d->idx % d->info->phil_num]);
	printf(BLUE "%f_in_ms %d has taken a fork" RESET "\n", (float)relative_time(d->info->start)/1000, d->idx);

	pthread_mutex_lock(&(data.fork[(d->idx + 1) % d->info->phil_num]));
	d->r = &(data.fork[(d->idx + 1) % d->info->phil_num]);
	printf(BLUE "%f_in_ms %d has taken a fork" RESET "\n", (float)relative_time(d->info->start)/1000, d->idx);
}

void thread_eat(t_personal_info *d)
{
	// 포크 2개를 집는다.
	thread_pick(d);
	// ===============critical section ======================

		// 먹는다.
		printf(YELLOW "%f_in_ms %d eating" RESET "\n", (float)relative_time(d->info->start)/1000, d->idx);
		usleep(d->info->phil_eat_time * 1000 * 1000);

		// 포크를 놓는다.
		d->l = NULL;
		d->r = NULL;

		//printf("[DEBUG] %d drop forks.\n", d->idx);
	// ===============critical section ======================
	pthread_mutex_unlock(&(data.fork[d->idx % d->info->phil_num]));
	pthread_mutex_unlock(&(data.fork[(d->idx + 1) % d->info->phil_num]));

	// 다 먹고나서부터 다시 시간측정.
	d->last_eat = get_time();
}

void thread_sleep(t_personal_info *d)
{
	printf(GREEN "%f_in_ms %d sleeping" RESET "\n", (float)relative_time(d->info->start)/1000, d->idx);
	usleep(d->info->phil_slp_time * 1000 * 1000);
}

void thread_think(t_personal_info *d)
{
	printf(MAGENTA "%f_in_ms %d thinking" RESET "\n", (float)relative_time(d->info->start)/1000, d->idx);
	// while(1)
	// {
	// 	// 쓰레드의 그룹이 식사할 권한을 얻는다면 break.
	// 	if (d->groupnum)	// 미완성..
	// 		break;
	// }
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
	// 마지막 식사시간~현재까지 시간차 < 수명 이라면 생존.
	//printf("수명체크 : %f , %f\n", (float)relative_time(d->last_eat)/1000, (float)(d->info->phil_life));
	return ((float)relative_time(d->last_eat)/1000 < (float)(d->info->phil_life));
}

// 죽는걸 어디서 검사해야 하지..?
void thread_AA(t_personal_info *d)
{
	// 홀짝 구분을 위한 시간차.
	if (d->idx % 2 == 1)
		usleep(1000);	// 0.001초 지연시키기.
	// 현재 쓰레드의 그룹 권한으로 먹을 수 있다면
	while(1)
	{
		// 생존체크.
		if (!thread_survive(d))
		{
			printf(RED "%f_in_ms %d died" RESET "\n", (float)relative_time(d->info->start)/1000, d->idx);
			return ;
		}

		if (d->groupnum)
		{
			thread_eat(d);
			thread_sleep(d);
		}
		// 먹을 수 없다면 THINK하며 기다림.
		else
			thread_think(d);
	}
}
