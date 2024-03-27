/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_atwork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:24:37 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 15:11:46 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void    ft_fork_taken(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d has taken a fork.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_eating_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is eating.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_sleeping_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is sleeping.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_thinking_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is thinking.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}


void    ft_death_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d has died.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_eat(t_args *args)
{
    ft_eating_msg(args);
    ft_wait(args->info->eating_time);
}

void    ft_sleep(t_args *args)
{
    ft_sleeping_msg(args);
    ft_wait(args->info->sleeping_time);
}

void    ft_think(t_args *args)
{
    ft_thinking_msg(args);
}

void    ft_monitor_time(t_args *args)
{
    if (args->counter[*args->phil_num-1] > args->info->time_to_die)
    {
        ft_death_msg(args);
        args->info->philo_died = 1;
    }
}

void *ft_eating(void *arg)
{
    t_args *args;

    args = (t_args *)arg;
    while (1)
    {
        pthread_mutex_lock(args->right_fork);
        ft_fork_taken(args);
        pthread_mutex_lock(args->left_fork);
        ft_fork_taken(args);
        ft_monitor_time(args);
        if (*args->philo_died)
            break ;
        ft_eat(args);
        pthread_mutex_unlock(args->right_fork);
        pthread_mutex_unlock(args->left_fork);
        ft_sleep(args);
        ft_think(args);
    }
    return (NULL);
}

static void ft_parse(t_args *args, t_info *info, int index)
{
    args->info = info;
    args->phil_num = &index+1; 
    args->philo_died = &info->philo_died;
    if (index == 0)
        args->left_fork = &info->fork[info->tot_philos-1];
    else
        args->left_fork = &info->fork[index-1];
    args->right_fork = &info->fork[index];
    args->print_lock= &info->print_lock;
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

void    ft_philos_atwork(t_philo *philo, t_info *info)
{
    while (++philo->idx < info->tot_philos)
    {
        ft_parse(&philo->args[philo->idx], info, philo->idx);
        if (philo->idx+1%2 == 0) 
        {
            write(1, "here\n", 5);
            ft_wait(10);
        }
        if (pthread_create(&philo->philosophers[philo->idx], NULL, &ft_eating, (void *)&philo->args[philo->idx]))
            return ;
    }       
    philo->idx = -1;
    while (++philo->idx < info->tot_philos)
    {
       if (pthread_join(philo->philosophers[philo->idx], NULL))
        return ;
       write(1, "here\n", 5);
    }
    ft_destroy_mutexes(info);
}

