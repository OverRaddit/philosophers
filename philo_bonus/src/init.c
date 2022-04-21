/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:22:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 12:20:21 by gshim            ###   ########.fr       */
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
		|| info->phil_slp_time <= 0 || ((argc == 6) && (info->phil_min_eat <= 0)))
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
	ret->die = data->die;
	ret->full = data->full;
	ret->last_eat = get_time();
	ret->eat_count = 0;
	return (ret);
}

bool	pthread_philo_init(t_info *info, t_data *data)
{
	int	i;
	int	ret;

	data->info = info;
	data->dead_idx = -1;

	if (!semaphore(&data->fork, "/fork", info->phil_num)
		|| !semaphore(&data->print, "/print", 1)
		|| !semaphore(&data->die, "/die", 0)
		|| !semaphore(&data->full, "/full", 0))
		return (false);

	i = 0;
	// thread to process
	while (i < info->phil_num)
	{
		ret = fork();
		if (ret == -1)
			return (false);
		else if (ret == 0)
		{	/* child process */
			t_personal_info *pinfo = get_personal_data(i, info, data);
			if (!pinfo)
				return (false);

			// 워커쓰레드
			pthread_t	philo;
			if (pthread_create(&philo, NULL, t_function, (void *)(get_personal_data(i, info, data))))
				return (false);

			// 모니터링 쓰레드(자신의 죽음 감시)
			pthread_t		monitor;
			pthread_create(&monitor, NULL, monitoring, (void *)&data);	// 어떻게보내지

			pthread_join(monitor, NULL);
			return (0);
		}
		i++;
	}
	return (true);
}
