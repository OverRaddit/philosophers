/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:20 by gshim             #+#    #+#             */
/*   Updated: 2022/04/19 15:54:10 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

// 공통정보
typedef struct s_info
{
	int		phil_num;
	int		phil_life;
	int		phil_eat_time;
	int		phil_slp_time;
	int		phil_min_eat;
}	t_info;

// 개인정보
typedef struct s_personal_info
{
	int				idx;
	t_info			*info;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*r;
	pthread_mutex_t	*l;
	size_t			last_eat;
	int				eat_count;
}	t_personal_info;

// 쓰레드 및 뮤텍스 데이터
typedef struct s_data
{
	pthread_t		phils[OPEN_MAX];

	t_personal_info	*phils_info[OPEN_MAX];
	pthread_mutex_t	fork[OPEN_MAX];
	pthread_mutex_t	printer;
	int				dead_idx;
	t_info			*info;
}	t_data;

// 로깅 유형
typedef enum e_phil_mode{
	INIT = 42,
	GRAB = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DIE = 4,
}	t_phil_mode;

//philosophers.c
void			logging(int mode, int idx, pthread_mutex_t *printer);
bool			get_info(int argc, char *argv[], t_info *info);

bool			pthread_philo_init(t_info *info, t_data *data);

// personal_info.c
bool			pthread_philo_init(t_info *info, t_data *data);
bool			get_info(int argc, char *argv[], t_info *info);
t_personal_info	*get_personal_data(int idx, t_info *info, t_data *data);

// thread.c
void			thread_pick(t_personal_info *d);
void			thread_eat(t_personal_info *d);
void			thread_sleep(t_personal_info *d);
void			thread_think(t_personal_info *d);
void			*t_function(void *data);

// monitor.c
bool			thread_survive(t_personal_info *d);
bool			thread_done(t_personal_info *d);
void			*monitoring(void *data);

// UTIL
int				ft_atoi(const char *str);
size_t			get_time(void);
size_t			relative_time(size_t start);
void			gsleep(size_t ms);

// ERROR.c
int				ft_exit(void (*f)(void), int ret);
#endif
