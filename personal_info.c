/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personal_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 22:22:53 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

enum e_phil_mode	get_mode(int idx, int groupnum)
{
	if (groupnum == 1)
	{
		return (EATING);
	}
	else if (groupnum == 2)
	{
		return (WAITING2);
	}
	else
	{
		return (WAITING1);
	}
}

int		get_groupnum(int idx, t_info *info)
{
	if (info->phil_num % 2 == 1)
	{
		// 마지막
		if (idx == info->phil_num - 1)
			return (3);
		// 홀수
		else if (idx % 2 == 1)
			return (1);
		// 짝수
		else
			return (2);
	}
	else
	{
		if (idx % 2 == 1)
			return (1);
		else
			return (2);
	}
}

t_personal_info	*get_personal_data(int idx, t_info *info)
{
	t_personal_info *ret;

	ret = malloc(sizeof(t_personal_info));
	ret->idx = idx;
	ret->groupnum = get_groupnum(idx, info);
	ret->mode = get_mode(idx, ret->groupnum);
	ret->info = info;
	return (ret);
}
