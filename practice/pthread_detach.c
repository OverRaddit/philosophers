/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_detach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:31:02 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 16:53:09 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 쓰레드 함수
// 5초간 머뭄뒤에 종료
void *t_function(void *data)
{
	char a[100000];   // 자원 점유!
	static int num = 0;
	num = *((int *)data);
	printf("Thread Start\n");
	sleep(5);
	printf("Thread end\n");
	return (void*)&num;
}

int main()
{
	pthread_t p_thread;
	int thr_id;
	int status;
	int a = 100;

	printf("Before Thread\n");
	thr_id = pthread_create(&p_thread, NULL, t_function, (void *)&a);
	if (thr_id < 0)
	{
		perror("thread create error : ");
		exit(0);
	}

	// pthread_detach() 없이 pause 상태 진입.
		// 자원 회수가 되지 않는다.

	// detach시켜주면 해당 쓰레드의 자원이 반납된다.
	pthread_detach(p_thread);

	pause();
	return 0;
}
