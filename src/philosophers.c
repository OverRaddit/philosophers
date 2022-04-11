/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:43:14 by gshim             #+#    #+#             */
/*   Updated: 2022/04/11 19:37:08 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	get_info(t_info *info, char *argv[])
{
	int i;

	i = 1;
	// 1 2 3 4 5(선택)
	// 각 인자값 유효검사 필요.
	info->phil_num = ft_atoi(argv[1]);
	info->phil_life = ft_atoi(argv[2]);
	info->phil_eat_time = ft_atoi(argv[3]);
	info->phil_slp_time = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info->phil_min_eat = ft_atoi(argv[5]);
}

static void	*t_function(void *data)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();

	// char* thread_name = (char*)data;
	// int i = 0;

	// // EAT
	// usleep(data->phil_eat_time * 1000000);
	// // SLEEP
	// usleep(data->phil_slp_time * 1000000);
	// // THINK
	// usleep(data->phil_eat_time * 1000000);
	t_personal_info *d = (t_personal_info *)data;
	printf("======================\n");
	printf("[%x] idx: %d, groupnum: %d, philsnum: %d\n", (unsigned int)tid, d->idx, d->groupnum, d->info->phil_num);
	printf("======================\n");

	if (d->groupnum == 1)
		;
	else if (d->groupnum == 2)
		;
	else

	return (0);
}

void	pthread_philo_init(t_info *info, t_data *data)
{
	int i;

	i = 0;
	// while(i < info->phil_num)
	// {
	// 	// 철학자(쓰레드) 생성
	// 	data->phils_id[i] = pthread_create(&data->phils[i], NULL,
	// 						 t_function, (void *)get_personal_data(i, info));
	// 	// 포크(뮤텍스) init
	// 	pthread_mutex_init(&(data->fork[i]), NULL);
	// }

	// [TEST] 2개의 철학자 생성.
	data->phils_id[0] = pthread_create(&data->phils[0], NULL,
	 						 t_function, (void *)get_personal_data(0, info));
	data->phils_id[1] = pthread_create(&data->phils[1], NULL,
	 						 t_function, (void *)get_personal_data(1, info));
}

// void	logging(enum e_phil_mode, int idx)
// {
// 	// 포크를 집었을 경우를 어떻게 처리...?
// 	if (e_phil_mode == EATING)
// 		printf("timestamp_in_ms %d is eating", idx);
// 	else if (e_phil_mode == SLEEPING)
// 		printf("timestamp_in_ms %d is sleeping", idx);
// 	else if (e_phil_mode == THINKING)
// 		printf("timestamp_in_ms %d is thinking", idx);
// 	else if (e_phil_mode == DIED)
// 		printf("timestamp_in_ms %d died", idx);
// }


// ./philosophers 2 10 3 3
// 철학자2, 수명10, 식사3, 수면3
int		main(int argc, char *argv[])
{
	t_info info;
	t_data data;
	//bool toggle;

	if (argc < 5)
		printf("few argument\n");
	else if (argc > 6)
		printf("too many argument\n");

	printf("[DEBUG]1\n");
	get_info(&info, argv);
	printf("[DEBUG]2\n");
	pthread_philo_init(&info, &data);
	printf("[DEBUG]3\n");
	//toggle = true;

	// 특정철학자(스레드)가 죽었거나, 모든 철학자(스레드)가 최소 식사횟수를 만족했다면
	// 종료한다.

	pthread_detach(data.phils[0]);
	pthread_detach(data.phils[1]);


	while(1)
	{
		;
	}
}
