/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:21:45 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 15:33:39 by gshim            ###   ########.fr       */
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

void	*monitoring(void *d)
{
	t_data	*data;
	int		i;

	data = (t_data *)d;
	t_personal_info *dd = data->phils_info[i];
	printf("MONITORING START!!\n");
	while(1)
	{
		i = 0;
		while(i < data->info->phil_num)
		{
			if (!thread_survive(data->phils_info[i]))	// i번째 쓰레드가 죽었다면,
			{
				data->dead_idx = i;
				return (0);
			}
			if (data->info->phil_min_eat != -1 && thread_done(data->phils_info[i])) // 식사횟수를 만족했다면
				return (0);
			i++;
		}
	}
}
