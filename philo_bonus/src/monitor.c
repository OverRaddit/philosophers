/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:21:45 by gshim             #+#    #+#             */
/*   Updated: 2022/04/22 12:08:51 by gshim            ###   ########.fr       */
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

void	*phil_monitoring(void *d)
{
	t_personal_info	*p;

	p = (t_personal_info *)d;
	sem_wait(p->full);
	while (1)
	{
		if (!thread_survive(p))
		{
			//printf("%d 사망\n", p->idx);
			exit(1);
		}
		if (p->info->phil_min_eat != -1
			&& thread_done(p))
		{
			//printf("%d 식사끝\n", p->idx);
			sem_post(p->full);
			exit(0);
		}
	}
}

void	*full_monitoring(void *d)
{
	t_data			*data;
	int				i;

	data = (t_data *)d;
	i = -1;
	while (++i < data->info->phil_num)
	{
		sem_wait(data->full);
	}
	philo_exit(data);
	return (0);
}
