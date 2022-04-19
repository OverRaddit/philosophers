/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:43:14 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 15:33:54 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// 오버플로 검사 필요...? 푸쉬스왑때의 코드를 찾아볼까!
bool	get_info(int argc, char *argv[], t_info *info)
{
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

void	*t_function(void *pinfo)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	thread_AA((t_personal_info *)pinfo);
	return (0);
}

bool	pthread_philo_init(t_info *info, t_data *data)
{
	int				i;

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
		if (pthread_create(&data->phils[i], NULL, t_function, (void *)(data->phils_info[i])))
			return (false);
		i++;
	}
	return (true);
}

void	logging(int mode, int idx, pthread_mutex_t *printer)
{
	static size_t	start;
	size_t			time;

	if (start == 0)
		start = get_time();

	pthread_mutex_lock(printer);
	time = relative_time(start)/1000;
	if (mode == GRAB)
		printf("%10zu_ms  " BLUE "%d has taken a fork" RESET "\n", time, idx);
	else if (mode == EAT)
		printf("%10zu_ms  " YELLOW "%d eating" RESET "\n", time, idx);
	else if (mode == SLEEP)
		printf("%10zu_ms  " GREEN "%d sleeping" RESET "\n", time, idx);
	else if (mode == THINK)
		printf("%10zu_ms  " MAGENTA "%d is thinking" RESET "\n", time, idx);
	else if (mode == DIE)
		printf("%10zu_ms  " RED "%d died" RESET "\n", time, idx);
	else if (mode == INIT)
		printf(GREEN "TIMER START!\n" RESET);
	pthread_mutex_unlock(printer);
}

void	philo_exit(t_data *data)
{
	if (data->dead_idx != -1)
	{ /* 특정 철학자 사망엔딩 */
		logging(DIE, data->dead_idx, &data->printer);
	}
	pthread_mutex_destroy(&(data->printer));
}

static void	usage(void)
{
	printf("You should type like..\n");
	printf(RED "./philosophers phil_num time_to_die time_to_eat time_to_sleep " RESET);
	printf(RED "[number_of_times_each_philosopher_must_eat]\n" RESET);
}

static void	thread(void)
{
	printf("There's something wrong in" RED "Thread\n" RESET);
}

int		main(int argc, char *argv[])
{
	t_data	data;
	t_info	info;

	if (argc < 5 || argc > 6 || !get_info(argc, argv, &info))	// 인자검사 추가할것.
		return (ft_exit(usage, -1));
	logging(INIT, 42, &data.printer);	// 최초의 start시간 측정
	printf("[DEBUG]INIT PHILO..\n");
	if (!pthread_philo_init(&info, &data))
		return (ft_exit(thread, -1));
	printf("[DEBUG]INIT COMPLETE\n");

	// DEBUG
	//printf(GREEN "%d<<\n" RESET,  data.info->phil_num);

	// 모니터링쓰레드 생성
	// 이게 여기말고 다른 구조체에 있어야 자연스럽다
	pthread_t monitor_thread;
	pthread_create(&monitor_thread, NULL, monitoring, (void *)&data);

	pthread_join(monitor_thread, NULL);
	philo_exit(&data);
	return (0);
}
