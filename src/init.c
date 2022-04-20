/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 17:44:26 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	get_info(int argc, char *argv[], t_info *info)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_valid(argv[i]) || ft_strlen(argv[i]) == 0)
			return (false);
	}
	info->phil_num = ft_atoi(argv[1]);
	info->phil_life = ft_atoi(argv[2]);
	info->phil_eat_time = ft_atoi(argv[3]);
	info->phil_slp_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->phil_min_eat = ft_atoi(argv[5]);
	else
		info->phil_min_eat = -1;
	if (info->phil_num == 0 || info->phil_life == 0 || info->phil_eat_time == 0
		|| info->phil_slp_time == 0 || info->phil_min_eat == 0)
		return (false);
	return (true);
}

t_personal_info	*get_personal_data(int idx, t_info *info, t_data *data)
{
	t_personal_info	*ret;

	ret = malloc(sizeof(t_personal_info));
	if (!ret)
		return (NULL);
	ret->idx = idx;
	ret->info = info;
	ret->printer = &data->printer;
	ret->r = &data->fork[idx % info->phil_num];
	ret->l = &data->fork[(idx + 1) % info->phil_num];
	ret->last_eat = get_time();
	ret->eat_count = 0;
	return (ret);
}

bool	pthread_philo_init(t_info *info, t_data *data)
{
	int	i;

	data->info = info;
	data->dead_idx = -1;
	if (pthread_mutex_init(&data->printer, NULL))
		return (false);
	i = 0;
	while (i < info->phil_num)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (false);
		data->phils_info[i] = get_personal_data(i, info, data);
		if (!data->phils_info[i])
			return (false);
		if (pthread_create(&data->phils[i], NULL
				, t_function, (void *)(data->phils_info[i])))
			return (false);
		i++;
	}
	return (true);
}
