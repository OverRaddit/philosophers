/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/22 18:04:31 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	get_info(int argc, char *argv[], t_info *info)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!is_valid(argv[i]) || ft_strlen(argv[i]) == 0)
			return (false);
	info->phil_num = ft_atoi(argv[1]);
	info->phil_life = ft_atoi(argv[2]);
	info->phil_eat_time = ft_atoi(argv[3]);
	info->phil_slp_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->phil_min_eat = ft_atoi(argv[5]);
	else
		info->phil_min_eat = -1;
	if (info->phil_num <= 0 || info->phil_life <= 0 || info->phil_eat_time <= 0
		|| info->phil_slp_time <= 0
		|| ((argc == 6) && (info->phil_min_eat <= 0)))
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
	ret->fork = data->fork;
	ret->print = data->print;
	ret->full = data->full;
	ret->last_eat = get_time();
	ret->eat_count = 0;
	return (ret);
}

bool	phil_process(int i, t_info *info, t_data *data)
{
	t_personal_info	*pinfo;
	pthread_t		philo;
	pthread_t		monitor;

	pinfo = get_personal_data(i, info, data);
	if (!pinfo)
		return (false);
	if (pthread_create(&philo, NULL, t_function, (void *)pinfo))
		return (false);
	if (pthread_create(&monitor, NULL, phil_monitoring, (void *)pinfo))
		return (false);
	pthread_join(monitor, NULL);
	exit(42);
}

bool	pthread_philo_init(t_info *info, t_data *data)
{
	int	i;
	int	ret;

	data->info = info;
	data->dead_idx = -1;
	if (!semaphore(&data->fork, "/fork", info->phil_num)
		|| !semaphore(&data->print, "/print", 1)
		|| !semaphore(&data->full, "/full", info->phil_num))
		return (false);
	i = -1;
	while (++i < info->phil_num)
	{
		ret = fork();
		if (ret == -1)
			return (false);
		if (ret == 0)
			return (phil_process(i, info, data));
		data->philo[i] = ret;
	}
	usleep(3000);
	if (pthread_create(&data->full_monitor,
			NULL, full_monitoring, (void *)data))
		return (false);
	return (true);
}
