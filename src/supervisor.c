/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 18:19:05 by gshim             #+#    #+#             */
/*   Updated: 2022/04/13 18:46:20 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	get_count(void)
{
	if (data.nextgroup == 1)
		return data.a_count;
	else if (data.nextgroup == 2)
		return data.b_count;
	else if (data.nextgroup == 3)
		return data.c_count;
	else
		return -1;
}

void	set_count(int count)
{
	if (data.nextgroup == 1)
		data.a_count += 1;
	else if (data.nextgroup == 2)
		data.b_count += 1;
	else if (data.nextgroup == 3)
		data.c_count += 1;
	else
		return ;
}

void	*supervising(void *dd)
{
	int			i;
	int			count;

	t_personal_info *d = (t_personal_info *)dd;
	printf("SUPERVISING START!!\n");

	count = get_count();

	// data->nextgroup에 속한 모든 철학자가 식사를 완료했는 지 체크한다.
	i = 0;	// 이걸 while밖에서 해도 될지도?
	while(i < info.phil_num)
	{
		// 현재 쓰레드가 식사그룹에 해당한다면
		if (get_groupnum(i, &info) == data.nextgroup)
		{
			if (data.phils_info[i]->eat_count <= count) // 식사 미완료
				continue;
		}
		i++;
	}

	printf("[%d] group finish their meal!!\n", data.nextgroup);
	set_count(count);
	data.nextgroup = (data.nextgroup + 1) % 2;	// 2그룹이면 2, 3그룹이면 3으로 %해야함.
	return (0);
}