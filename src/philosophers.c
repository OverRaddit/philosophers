/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:43:14 by gshim             #+#    #+#             */
/*   Updated: 2022/04/17 18:51:20 by gshim            ###   ########.fr       */
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
	else
		info->phil_min_eat = -1;
	//gettimeofday(&(info->start), NULL);
	info->start = get_time();
}

void	*t_function(void *data)
{
	pid_t		pid;
	pthread_t	tid;
	struct timeval time;

	pid = getpid();
	tid = pthread_self();

	t_personal_info *d = (t_personal_info *)data;
	gettimeofday(&time, NULL);

	thread_AA(d);
	printf("thread exit\n");
	return (0);
}

void	pthread_philo_init(t_info *info, t_data *data)
{
	int i;

	data->nextgroup = 1;
	data->a_count = 0;
	data->b_count = 0;
	data->c_count = 0;
	pthread_mutex_init(&data->printer, NULL);
	i = 0;
	while(i < info->phil_num)
	{
		// 포크(뮤텍스) 생성
		pthread_mutex_init(&data->fork[i], NULL);
		// 철학자(쓰레드) 생성
		data->phils_info[i] = get_personal_data(i, info);
		data->phils_id[i] = pthread_create(&data->phils[i], NULL,
							 t_function, (void *)(data->phils_info[i]));
		i++;
	}
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
// 철학자2, 수명5, 식사3, 수면3
int		main(int argc, char *argv[])
{
	//bool toggle;

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

	pthread_t supervisor_thread;
	if (false)
		pthread_create(&supervisor_thread, NULL, supervising, (void *)"supervising");

	// 특정철학자(스레드)가 죽었거나, 모든 철학자(스레드)가 최소 식사횟수를 만족했다면
	// 종료한다.

	// detach, join둘다 안하면 어떻게되지?

	int s = 0;
	pthread_join(monitor_thread, NULL);
	pthread_mutex_lock(&(data.printer)); // 다른 쓰레드들이 출력하지 못하게 막는다.
	printf("EXIT DETECTED!!\n");
	return (0);
}

// typedef struct        s_philo
// {
//    pthread_t         tid;
//     int               num;
//     int               r_fork;
//     int               l_fork;
//     int               eat_cnt;
//     struct s_rule     *rule;
//     struct s_mutex    *mutex;
//     struct timeval    start_tv;
//     struct timeval    life_tv;
// }                     t_philo;