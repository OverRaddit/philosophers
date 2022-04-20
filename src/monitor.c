/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:21:45 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 20:01:47 by gshim            ###   ########.fr       */
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
	int		full_num;

	data = (t_data *)d;
	printf("MONITORING START!!\n");
	while (1)
	{
		i = 0;
		full_num = 0;
		while (i < data->info->phil_num)
		{
			if (!thread_survive(data->phils_info[i]))
			{
				data->dead_idx = i;
				return (0);
			}
			if (data->info->phil_min_eat != -1
				&& thread_done(data->phils_info[i]))
				full_num++;
			i++;
		}
		if (data->info->phil_min_eat != -1 && full_num == data->info->phil_num)
			return (0);
	}
}
