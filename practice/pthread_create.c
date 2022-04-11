/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_practice.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:02 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 16:37:59 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void	*t_function(void *data)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();

	char* thread_name = (char*)data;
	int i = 0;

	while(i < 3)
	{
		printf("[%s] pid:%u, tid:%x --- %d\n", thread_name, (unsigned int)pid, (unsigned int)tid, i);
		i++;
		sleep(1); // usleep이랑 차이?
	}
}

int main()
{
	pthread_t p_thread[2];
	int thr_id;
	int status;

	char p1[] = "th1";
	char p2[] = "th2";
	char pM[] = "th3";

	sleep(1);

	thr_id = pthread_create(&p_thread[0], NULL, t_function, (void *)p1);
	if (thr_id < 0)
	{
		perror("error: ");
		exit(0);
	}

	thr_id = pthread_create(&p_thread[1], NULL, t_function, (void *)p2);
	if (thr_id < 0)
	{
		perror("error: ");
		exit(0);
	}

	t_function((void *)pM);

	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	printf("언제 종료 될까요?\n");
	return 0;
}