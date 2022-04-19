/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personal_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 14:16:49 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_personal_info	*get_personal_data(int idx, t_info *info, t_data *data)
{
	t_personal_info *ret;

	ret = malloc(sizeof(t_personal_info));
	if (!ret)
		return (NULL);
	ret->idx = idx;
	ret->info = info;
	ret->printer = &data->printer;
	ret->r = &data->fork[idx];
	ret->l = &data->fork[idx + 1];
	ret->last_eat = get_time();
	ret->eat_count = 0;
	return (ret);
}
