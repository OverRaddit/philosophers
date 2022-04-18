/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:43:14 by gshim             #+#    #+#             */
/*   Updated: 2022/04/18 22:10:09 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	get_info(t_info *info, char *argv[])
{
	int i;

	i = 1;
	info->phil_num = ft_atoi(argv[1]);
	info->phil_life = ft_atoi(argv[2]);
	info->phil_eat_time = ft_atoi(argv[3]);
	info->phil_slp_time = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info->phil_min_eat = ft_atoi(argv[5]);
	else
		info->phil_min_eat = -1;
	info->start = get_time();
}

void	*t_function(void *data)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	thread_AA((t_data *)data);
	return (0);
}

void	pthread_philo_init(t_info *info, t_data *data)
{
	int i;

	data->dead_idx = -1;
	pthread_mutex_init(&data->printer, NULL);
	i = 0;
	while(i < info->phil_num)
	{
		// 포크(뮤텍스) 생성
		pthread_mutex_init(&data->fork[i], NULL);
		// 철학자(쓰레드) 생성
		data->phils_info[i] = get_personal_data(i, info, data);
		data->phils_id[i] = pthread_create(&data->phils[i], NULL,
							 t_function, (void *)(data));
		i++;
	}
}

void	logging(int mode, int idx)
{
	size_t time;

	pthread_mutex_lock(&(data.printer));
	time = relative_time(info.start)/1000;
	if (mode == GRAB)
		printf("%10zu_ms  " BLUE "%d has taken a fork" RESET "\n", time, idx);
	else if (mode == EAT)
		printf("%10zu_ms  " YELLOW "%d eating" RESET "\n", time, idx);
	else if (mode == SLEEP)
		printf("%10zu_ms  " GREEN "%d sleeping" RESET "\n", time, idx);
	else if (mode == THINK)
		printf("%10zu_ms  " MAGENTA "%d is thinking" RESET "\n", time, idx);
	else if (mode == DIE)
		printf("%10zu_ms  " RED "%d died" RESET "\n", time, data.dead_idx);
	pthread_mutex_unlock(&(data.printer));
}

void	philo_exit(t_data *data)
{
	if (data->dead_idx != -1)
	{ /* 특정 철학자 사망엔딩 */
		logging(DIE, data->dead_idx);
	}
	pthread_mutex_destroy(&(data->printer));
}

int		main(int argc, char *argv[])
{
	t_data	data;
	t_info	info;

	if (argc < 5)
		printf("few argument\n");
	else if (argc > 6)
		printf("too many argument\n");

	printf("[DEBUG]Get ARGV INFO..\n");
	get_info(&info, argv);
	printf("[DEBUG]INIT PHILO..\n");
	pthread_philo_init(&info, &data);
	printf("[DEBUG]INIT COMPLETE\n");

	// 모니터링쓰레드 생성
	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitoring, (void *)"monitoring");

	// detach, join둘다 안하면 어떻게되지?
	// 철학자 쓰레드를 detach 해줘야 하나?

	pthread_join(monitor_thread, NULL);
	philo_exit(&data);
	return (0);
}
