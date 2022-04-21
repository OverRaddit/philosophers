/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:43:14 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 12:22:09 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	logging(int mode, int idx, sem_t *printer)
{
	static size_t	start;
	size_t			time;

	if (start == 0)
		start = get_time();
	sem_wait(printer);
	time = relative_time(start) / 1000;
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
	else if (mode == FULL)
		printf(GREEN "Every philosopher is full!\n" RESET);
	sem_post(printer);
}

void	philo_exit(t_data *data)
{
	if (data->dead_idx != -1)
		logging(DIE, data->dead_idx, data->print);
	else
		logging(FULL, data->dead_idx, data->print);
	pthread_mutex_destroy(data->print);

	// 자식프로세스 kill 시그널

	// 세마포 삭제
	if (sem_close(data->fork) || sem_close(data->print)
		|| sem_close(data->die) || sem_close(data->full))
			stderror(errno);
}

static void	usage(void)
{
	printf(RED "./philosophers phil_num time_to_die " RESET);
	printf(RED "time_to_eat time_to_sleep " RESET);
	printf(RED "[number_of_times_each_philosopher_must_eat]\n" RESET);
}

static void	fork(void)
{
	printf("There's something wrong in" RED "Fork\n" RESET);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_info		info;

	if (argc < 5 || argc > 6 || !get_info(argc, argv, &info))
		return (ft_exit(usage, -1));
	logging(INIT, -42, &data.print);
	if (!pthread_philo_init(&info, &data))
		return (ft_exit(fork, -1));

	// waitpid
	waitpid(-1);

	philo_exit(&data);
	return (0);
}
