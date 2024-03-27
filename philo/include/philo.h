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
	int philo_died;
	long long start_time;
	pthread_mutex_t fork[200];
	pthread_mutex_t	print_lock;
} t_info;

typedef struct s_args
{
	int counter[200];
	int *phil_num;
	int *philo_died;
	t_info *info;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t	*print_lock;
}	t_args;

typedef struct s_philo
{
	pthread_t philosophers[200];
	t_args args[200];
	int idx;
}	t_philo;



void	ft_save_info(t_info *info, int argc, char **argv);
void	ft_philo_init(t_philo *philo);
long long ft_current_time();
void    ft_wait(long long time);
void    ft_philos_atwork(t_philo *philo, t_info *info);
void    ft_init_forks(t_info *info);
void    ft_destroy_mutexes(t_info *info);

#endif
