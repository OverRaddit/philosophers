/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:45:20 by gshim             #+#    #+#             */
/*   Updated: 2022/04/21 15:11:06 by gshim            ###   ########.fr       */
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
# include <errno.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

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
	size_t	phil_life;
	size_t	phil_eat_time;
	size_t	phil_slp_time;
	int		phil_min_eat;
}	t_info;

// 개인정보
typedef struct s_personal_info
{
	int				idx;
	t_info			*info;

	sem_t			*fork;
	sem_t			*print;
	sem_t			*die;
	sem_t			*full;

	size_t			last_eat;
	int				eat_count;
}	t_personal_info;

// 쓰레드 및 뮤텍스 데이터
typedef struct s_data
{
	//pthread_t		phils[OPEN_MAX];
	//t_personal_info	*phils_info[OPEN_MAX];
	pid_t			philo[OPEN_MAX];

	sem_t			*fork;
	sem_t			*print;
	sem_t			*die;
	sem_t			*full;

	pthread_t		monitor_thread;
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
	FULL = 5,
}	t_phil_mode;

//philosophers.c
void			logging(int mode, int idx, sem_t *printer);
bool			get_info(int argc, char *argv[], t_info *info);
bool			pthread_philo_init(t_info *info, t_data *data);

// init.c
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
size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
size_t			get_time(void);
size_t			relative_time(size_t start);
void			gsleep(size_t ms);

// ERROR.c
int				ft_exit(void (*f)(void), int ret);

// valid.c
int				is_valid(char *input);

// semaphore.c
bool			semaphore(sem_t **sem, char *filename, size_t size);

#endif
