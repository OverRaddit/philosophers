/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:21:45 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 12:17:28 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	thread_survive(t_personal_info *d)
{
	return (relative_time(d->last_eat) <= (d->info->phil_life) * 1000);
}

bool	thread_done(t_personal_info *d)
{
	return (d->eat_count == d->info->phil_min_eat);
}


// 자기자신만 보면 된다.
void	*monitoring(void *d)
{
	t_personal_info	*pinfo;
	int		i;
	int		full_num;

	pinfo = (t_personal_info *)d;
	printf("MONITORING START!!\n");
	while (1)
	{
		i = 0;
		full_num = 0;
		while (i < pinfo->info->phil_num)
		{
			if (!thread_survive(pinfo))
			{
				//data->dead_idx = i; => 이걸 어떻게 대체하지? 해당 프로세스가 몇번 철학자인지 어떻게 알려줌?
				sem_wait(pinfo->die);
				return (0);
			}
			if (pinfo->info->phil_min_eat != -1
				&& thread_done(pinfo)
				sem_wait(pinfo->full);
			i++;
		}
		if (data->info->phil_min_eat != -1 && full_num == data->info->phil_num)
			return (0);
	}
}
