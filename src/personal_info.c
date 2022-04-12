/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personal_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/12 01:22:23 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		get_mode(int groupnum)
{
	if (groupnum == 1)
		return (EATING);
	else if (groupnum == 2)
		return (WAITING2);
	else
		return (WAITING1);
}

int		get_groupnum(int idx, t_info *info)
{
	// 마지막(철학자 수가 홀수일 때만 정의됨)
	if (info->phil_num % 2 == 1 && idx == info->phil_num - 1)
		return (3);
	// 짝수
	else if (idx % 2 == 0)
		return (1);
	// 홀수
	else
		return (2);
}

t_personal_info	*get_personal_data(int idx, t_info *info)
{
	t_personal_info *ret;

	ret = malloc(sizeof(t_personal_info));
	ret->idx = idx;
	ret->groupnum = get_groupnum(idx, info);
	ret->mode = get_mode(ret->groupnum);
	ret->info = info;
	return (ret);
}
