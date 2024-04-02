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
    pthread_mutex_destroy(&(info->stop_lock));
}

int ft_allocatetime(t_args *args)
{
    args->time->time_counter = (int *)malloc(sizeof(int));
    if (!args->time->time_counter)
        return (0);
    args->time->meal_counter = (int *)malloc(sizeof(int));
    if (!args->time->meal_counter)
        return (0);
    args->time->start_counter = (int *)malloc(sizeof(int));
    if (!args->time->start_counter)
        return (0);
    args->time->start = (int *)malloc(sizeof(int));
    if (!args->time->start)
        return (0);
    args->time->current_time = (long *)malloc(sizeof(int));
    if (!args->time->current_time)
        return (0);
    return (1);
}

int ft_allocatelog(t_args *args)
{
    args->log->eaten = (int *)malloc(sizeof(int));
    if (!args->log->eaten)
        return (0);
    args->log->eaten_time = (int *)malloc(sizeof(int));
    if (!args->log->eaten_time)
        return (0);
    args->log->slept = (int *)malloc(sizeof(int));
    if (!args->log->slept)
        return (0);
    args->log->slept_time = (int *)malloc(sizeof(int));
    if (!args->log->slept_time)
        return (0);
    args->log->thought = (int *)malloc(sizeof(int));
    if (!args->log->thought)
        return (0);
    args->log->thought_time = (int *)malloc(sizeof(int));
    if (!args->log->thought_time)
        return (0);
    args->log->died = (int *)malloc(sizeof(int));
    if (!args->log->died)
        return (0);
    args->log->died_time = (int *)malloc(sizeof(int));
    if (!args->log->died_time)
        return (0);
    args->log->left_fork_taken = (int *)malloc(sizeof(int));
    if (!args->log->left_fork_taken)
        return (0);
    args->log->left_fork_taken_time = (int *)malloc(sizeof(int));
    if (!args->log->left_fork_taken_time)
        return (0);
    args->log->right_fork_taken = (int *)malloc(sizeof(int));
    if (!args->log->right_fork_taken)
        return (0);
    args->log->right_fork_taken_time = (int *)malloc(sizeof(int));
    if (!args->log->right_fork_taken_time)
        return (0);
    return (1);
}
int ft_parse(t_args *args, t_info *info, t_philo *philo)
{
    args->info = info;
    args->time = &philo->time[philo->idx];
    if (!ft_allocatetime(args))
        return (0);
    args->log = &philo->log[philo->idx];
    if (!ft_allocatelog(args))
        return (0);
    philo->phil_num[philo->idx] = philo->idx+1; 
    args->phil_num = &philo->phil_num[philo->idx]; 
    args->philo_died = &info->philo_died;
    if (philo->idx == 0)
        args->right_fork = &info->fork[info->tot_philos-1];
    else
        args->right_fork = &info->fork[philo->idx-1];
    args->left_fork = &info->fork[philo->idx];
    args->print_lock= &info->print_lock;
    args->stop_lock= &info->stop_lock;
    return (1);
}
