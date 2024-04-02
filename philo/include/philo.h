/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:45 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 14:36:39 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "sys/time.h"
#include <sys/_pthread/_pthread_mutex_t.h>

typedef struct s_info
{
	int tot_philos;
	int time_to_die;
	int eating_time;
	int sleeping_time;
	int n_times_eat;	
	int last_meal;
	int philo_died;
	long start_time;
	pthread_mutex_t fork[200];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
} t_info;

typedef struct s_time
{
	int *time_counter;
	int *meal_counter;
	int *start_counter;
	int *start;
	long *current_time;
} t_time;

typedef struct s_log
{
	int *left_fork_taken;
	int *left_fork_taken_time;
	int *right_fork_taken;
	int *right_fork_taken_time;
	int *eaten;
	int *eaten_time;
	int *slept;
	int *slept_time;
	int *thought;
	int *thought_time;
	int *died;
	int *died_time;
} t_log;

typedef struct s_args
{
	int *phil_num;
	int *philo_died;
	t_info *info;
	t_time *time;
	t_log	*log;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*stop_lock;
}	t_args;

typedef struct s_philo
{
	pthread_t philosophers[200];
	t_args args[200];
	t_time time[200];
	t_log log[200];
	int phil_num[200];
	int idx;
}	t_philo;

/* ************ PRINTING MESSAGES *************** */
void    ft_fork_msg(t_args *args);
void    ft_eating_msg(t_args *args);
void    ft_fork_taken(t_args *args);
void    ft_death_msg(t_args *args);
void    ft_sleeping_msg(t_args *args);
void    ft_thinking_msg(t_args *args);

/* ************ ARGUMENTS VALIDATION *************** */
int ft_valid_args(int argc, char **argv, t_info *info);

/* ************ INIT STRUCTS *************** */
void	ft_save_info(t_info *info);

/* ************ PARSING *************** */
int ft_parse(t_args *args, t_info *info, t_philo *philo);

/* ************ PHILOS AT WORK *************** */
void	ft_philo_init(t_philo *philo);
long ft_current_time();
void    ft_wait(long time);
void    ft_philos_atwork(t_philo *philo, t_info *info);
void    ft_init_forks(t_info *info);
void    ft_destroy_mutexes(t_info *info);
void    ft_destroy_mutexes(t_info *info);
void    ft_init_forks(t_info *info);
void    ft_think(t_args *args);
void    ft_sleep(t_args *args);
void    ft_eat(t_args *args);
void    ft_monitor_time(t_args *args, int wait);
int ft_stop_simulation(t_args *args, int wait, int unlock);

#endif
