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

typedef struct s_fork
{
	pthread_mutex_t fork_lock;
}	t_fork;

typedef struct s_info
{
	int idx;
	int dead;
	int tot_philos;
	int philo_died;
	int start_time;
	int phil_time;
	long long time_to_die;
	long long eating_time;
	long long sleeping_time;
	int n_times_eat;	
} t_info;

typedef struct s_locks
{
	pthread_mutex_t print_lock;
	pthread_mutex_t	start_lock;
}	t_locks;

typedef struct s_philo
{
	int idx;
	int counter;
	int *phil_num;
	int *start_time;
	int *last_eat_time;
	t_info *info;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_mutex_t *print_lock;
	pthread_mutex_t	*start_lock;
}	t_philo;



int	ft_save_args(t_info *info, int n_args, char **argv);
long long ft_current_time();
void    ft_wait(long long time);
void    ft_philos_atwork(t_info *info);

#endif
