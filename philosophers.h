/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:20 by gshim             #+#    #+#             */
/*   Updated: 2022/04/12 16:20:31 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>	// gettimeofday함수

// 전역변수로 두면 깔끔할 것 같은데...
typedef struct s_info
{
	// common data
	int	phil_num;		// 철학자수(=포크수)
	int	phil_life;		// 수명
	int	phil_eat_time;	// 식사소요시간
	int	phil_slp_time;	// 수면시간
	int	phil_min_eat;	// 선택사항) 최소 식사횟수
	size_t start;		// timestamp용 시간변수
} t_info;

// 각 쓰레드에게 넘겨줘야 할 인자 값!
typedef struct s_personal_info
{
	// private data
	int		idx;			// 몇번 철학자인지 저장
	int		mode;			// 현재 상태를 저장
	int		groupnum;		// 어느그룹에 속했는지 저장
	t_info	*info;
	size_t last_eat;		// 마지막에 밥먹은 시간.
} t_personal_info;

typedef struct s_data
{
	pthread_t		phils[OPEN_MAX];		// 철학자쓰레드
	int				phils_id[OPEN_MAX];		// 철학자쓰레드id
	pthread_mutex_t	fork[OPEN_MAX];			// 포크뮤텍스
} t_data;

enum e_phil_mode {
	WAITING1 = -2,	// 대기중...
	WAITING2 = -1,	// 대기중...
	EATING = 0,		// 쿰척쿰척
	SLEEPING = 1,	// 잠자는중!
	THINKING = 2,	// 생각중!
	DIED = 3,		// 밥 못먹어서 죽었음 => 쓰레드종료
	FULL = 4,		// 최소 식사횟수를 만족함 => 쓰레드종료
};

//philosophers.c
void	get_info(t_info *info, char *argv[]);
void	*t_function(void *data);
void	pthread_philo_init(t_info *info, t_data *data);

// personal_info.c
int		get_mode(int groupnum);
int		get_groupnum(int idx, t_info *info);
t_personal_info	*get_personal_data(int idx, t_info *info);

// thread.c
void	thread_A(t_personal_info *d);

// UTIL
int	ft_atoi(const char *str);
size_t	get_time();
size_t	relative_time(size_t start);
