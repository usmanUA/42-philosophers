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
	int fork;
	pthread_mutex_t *fork_lock;
}	t_fork;

typedef struct s_data
{
	int tot_philos;
	int time_to_die;
	int eating_time;
	int sleeping_time;
	int n_times_eat;	
} t_data;

typedef struct s_philo
{
	int *phil_num;
	t_data *data;
	t_fork *left_fork;
	t_fork *right_fork;
	struct timeval start;
	struct timeval end;
	pthread_mutex_t	print_lock;
	pthread_mutex_t start_lock;
}	t_philo;



void ft_save_args(t_data *data, int n_args, char **argv);
void    ft_philos_atwork(t_data *data);

#endif
