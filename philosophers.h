/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:20 by gshim             #+#    #+#             */
/*   Updated: 2022/04/17 16:55:11 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>	// gettimeofday함수

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"


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
	pthread_mutex_t *l;
	pthread_mutex_t *r;
	t_info	*info;	// 내용물과 가르키는 것을 바꿀수 없게 만들고싶다.
	size_t last_eat;		// 마지막에 밥먹은 시간.
	int		eat_count;		// 밥을 먹은 횟수. 먹을때마다 증가시키기.
} t_personal_info;

typedef struct s_data
{
	pthread_t		phils[OPEN_MAX];		// 철학자쓰레드
	int				phils_id[OPEN_MAX];		// 철학자쓰레드id
	t_personal_info	*phils_info[OPEN_MAX];	// 각 철학자의 data
	pthread_mutex_t	fork[OPEN_MAX];			// i번째 포크의 상태(fork[i] = j => i번째포크를 j가 소유함.)
	pthread_mutex_t	group_mutex[3];			// 각 그룹별 권한 2=최고등급, 1=서브등급, 0무등급
	pthread_mutex_t	printer;				// 출력권한 뮤텍스
	bool			is_dead[OPEN_MAX];		// i번째 철학자의 상태(1=dead)
	int				nextgroup;				// 다음식사할 그룹번호
	int				a_count;
	int				b_count;
	int				c_count;
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

// 전역변수
t_info info;
t_data data;

//philosophers.c
void	get_info(t_info *info, char *argv[]);
void	*t_function(void *data);
void	pthread_philo_init(t_info *info, t_data *data);

// personal_info.c
int		get_mode(int groupnum);
int		get_groupnum(int idx, t_info *info);
t_personal_info	*get_personal_data(int idx, t_info *info);

// thread.c
void	thread_AA(t_personal_info *d);
void	thread_A(t_personal_info *d);

// monitor.c
bool	thread_survive(t_personal_info *d);
bool	thread_done(t_personal_info *d);
void	*monitoring(void *data);

// supervisor.c
void	*supervising(void *dd);

// UTIL
int	ft_atoi(const char *str);
size_t	get_time();
size_t	relative_time(size_t start);
