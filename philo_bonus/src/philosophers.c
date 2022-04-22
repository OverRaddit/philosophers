/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:43:14 by gshim             #+#    #+#             */
/*   Updated: 2022/04/22 21:33:28 by gshim            ###   ########.fr       */
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
	else
	{
		if (mode == DIE)
			printf("%10zu_ms  " RED "%d died" RESET "\n", time, idx);
		else if (mode == FULL)
			printf(GREEN "Every philosopher is full!\n" RESET);
		return ;
	}
	sem_post(printer);
}

static void	usage(void)
{
	printf(RED "./philosophers phil_num time_to_die " RESET);
	printf(RED "time_to_eat time_to_sleep " RESET);
	printf(RED "[number_of_times_each_philosopher_must_eat]\n" RESET);
}

static void	process(void)
{
	printf("There's something wrong in" RED " Fork()\n" RESET);
}

void	philo_exit(t_data *data)
{
	int	i;

	if (data->dead_idx != -1)
		logging(DIE, data->dead_idx, data->print);
	else
		logging(FULL, data->dead_idx, data->print);
	i = -1;
	while (++i < data->info->phil_num)
		kill(data->philo[i], SIGKILL);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_info		info;
	pid_t		pid;
	int			status;

	if (argc < 5 || argc > 6 || !get_info(argc, argv, &info))
		return (ft_exit(usage, -1));
	logging(INIT, -42, data.print);
	if (!pthread_philo_init(&info, &data))
		return (ft_exit(process, -1));
	get_die_phil(&data, &info);
	philo_exit(&data);
	return (0);
}
