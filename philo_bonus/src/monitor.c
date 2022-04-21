/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:21:45 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 22:50:03 by gshim            ###   ########.fr       */
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
	t_personal_info	*p;
	int		i;

	p = (t_personal_info *)d;
	printf("MONITORING START!!\n");
	while (1)
	{
		i = 0;
		full_num = 0;
		while (i < p->info->phil_num)
		{
			if (!thread_survive(p))
			{
				//sem_post(p->die);
				exit(1);
			}
			if (p->info->phil_min_eat != -1
				&& thread_done(p))
				full_num++;
			i++;
		}
	}
}
