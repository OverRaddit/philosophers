/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:21:45 by gshim             #+#    #+#             */
/*   Updated: 2022/04/13 22:37:12 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	thread_survive(t_personal_info *d)
{
	// 마지막 식사시간~현재까지 시간차 < 수명 이라면 생존.
	//printf("수명체크 : %f , %f\n", (float)relative_time(d->last_eat)/1000, (float)(d->info->phil_life));
	return ((float)relative_time(d->last_eat)/1000000 < (float)(d->info->phil_life));
}

bool	thread_done(t_personal_info *d)
{
	return (d->eat_count == d->info->phil_min_eat);
}

void	*monitoring(void *dd)
{
	pid_t		pid;
	pthread_t	tid;
	struct timeval time;
	int			i;

	pid = getpid();
	tid = pthread_self();

	t_personal_info *d = (t_personal_info *)dd;

	printf("MONITORING START!!\n");
	// 종료조건 무한검사.
	while(1)
	{
		i = 0;
		while(i < info.phil_num)
		{
			if (!thread_survive(data.phils_info[i]))	// i번째 쓰레드가 죽었다면,
			{
				size_t ttime = relative_time(data.phils_info[i]->info->start)/1000;
				usleep(100);
				printf(RED "%zu_in_ms %d died" RESET "\n", ttime, i);
				return 0;
			}
			if (info.phil_min_eat != -1 && thread_done(data.phils_info[i])) // 식사횟수를 만족했다면
				return 0;
			i++;
		}
	}
	return (0);
}