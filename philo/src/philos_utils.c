/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:02:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 14:19:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long ft_current_time()
{
    struct timeval time_val;

    gettimeofday(&time_val, NULL);
    return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

void    ft_wait(long time)
{
    long end;

    ft_current_time(); 
    end = ft_current_time() + time; 
    while (ft_current_time() < end)
        usleep(10);
}

void    ft_init_forks(t_info *info)
{
    int ind;

    ind = -1;
    while (++ind < info->tot_philos)
        pthread_mutex_init(&info->fork[ind], NULL);
}


void    ft_destroy_mutexes(t_info *info)
{
    int ind;

    ind = -1;
    while (++ind < info->tot_philos)
        pthread_mutex_destroy(&info->fork[ind]);
    pthread_mutex_destroy(&(info->print_lock));
}

void ft_parse(t_args *args, t_info *info, t_philo *philo)
{
    args->info = info;
    philo->phil_num[philo->idx] = philo->idx+1; 
    args->phil_num = &philo->phil_num[philo->idx]; 
    args->time_counter = &philo->time_counter[philo->idx]; 
    args->meal_counter = &philo->meal_counter[philo->idx]; 
    args->start_counter = &philo->start_counter[philo->idx]; 
    args->start = &philo->start[philo->idx]; 
    args->current_time= &philo->current_time[philo->idx]; 
    args->philo_died = &info->philo_died;
    if (philo->idx == 0)
        args->right_fork = &info->fork[info->tot_philos-1];
    else
        args->right_fork = &info->fork[philo->idx-1];
    args->left_fork = &info->fork[philo->idx];
    args->print_lock= &info->print_lock;
    args->stop_lock= &info->stop_lock;
    args->left_fork_taken = &info->left_fork_taken;
    args->right_fork_taken = &info->right_fork_taken;
    args->eaten = &info->eaten;
    args->slept = &info->slept;
    args->thought = &info->thought;
    args->died = &info->died;
}
