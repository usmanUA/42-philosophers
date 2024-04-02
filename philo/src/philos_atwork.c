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
#include <pthread.h>

static void    ft_handle_one(t_args *args)
{
    pthread_mutex_lock(args->left_fork);
    ft_fork_msg(args);
    ft_wait(args->info->time_to_die);
    ft_death_msg(args);
    pthread_mutex_unlock(args->left_fork);
    
}

static void *ft_eating(void *arg)
{
    t_args *args;

    args = (t_args *)arg;
    if (args->info->tot_philos == 1)
    {
        ft_handle_one(args);
        return (NULL);
    }
    if (*(args->phil_num)%2 == 0)
        ft_wait(10);
    while (1)
    {
        pthread_mutex_lock(args->left_fork);
        *args->log->left_fork_taken = 1;
        *args->log->left_fork_taken_time = ft_current_time() - args->info->start_time;
        pthread_mutex_lock(args->right_fork);
        *args->log->right_fork_taken = 1;
        *args->log->right_fork_taken_time = ft_current_time() - args->info->start_time;
        if (ft_stop_simulation(args, 0, 1))
            break ;
        /* write(1, "here\n", 5); */
        *args->time->current_time = ft_current_time();
        ft_eat(args); 
        pthread_mutex_unlock(args->left_fork);
        pthread_mutex_unlock(args->right_fork);
        if (ft_stop_simulation(args, 0, 0))
            break ;
        ft_sleep(args);
        if (ft_stop_simulation(args, 0, 0))
            break ;
        ft_think(args);
        if (ft_stop_simulation(args, 1, 0))
            break ;
    }
    return (NULL);
}


static void *ft_print_func(void *arg)
{
    t_args *args;
    int ind;
    int stop;

    args = (t_args *)arg;
    ind = -1;
    stop = 0;
    while (1)
    {
        /* write(1, "here\n", 5); */
        ind = -1;
        while (++ind < args[0].info->tot_philos)
        {
            if (*args[ind].log->left_fork_taken)
            {
                ft_fork_msg(&args[ind]);
                *args[ind].log->left_fork_taken = 0;
            }
            if (*args[ind].log->right_fork_taken)
            {
                ft_fork_msg(&args[ind]);
                *args[ind].log->right_fork_taken = 0;
            }
            if (*args[ind].log->eaten)
            {
                ft_eating_msg(&args[ind]);
                *args[ind].log->eaten = 0;
            }
            if (*args[ind].log->slept)
            {
                ft_sleeping_msg(&args[ind]);
                *args[ind].log->slept = 0;
            }
            if (*args[ind].log->thought)
            {
                ft_thinking_msg(&args[ind]);
                *args[ind].log->thought = 0;
            }
            if (*args[ind].log->died)
            {
                ft_death_msg(&args[ind]);
                *args[ind].log->died = 0;
                stop = 1;
                break ;
            }
            if (stop)
                break ;
        }
    }
    return (NULL);
}

void    ft_free(t_args *args, t_info *info)
{
    int ind;

    ind = -1;
    while (++ind < info->tot_philos)
    {
       free(args[ind].log->died); 
       free(args[ind].log->died_time); 
       free(args[ind].log->eaten); 
       free(args[ind].log->eaten_time); 
       free(args[ind].log->slept); 
       free(args[ind].log->slept_time); 
       free(args[ind].log->thought); 
       free(args[ind].log->thought_time); 
       free(args[ind].log->left_fork_taken); 
       free(args[ind].log->left_fork_taken_time); 
       free(args[ind].log->right_fork_taken); 
       free(args[ind].log->right_fork_taken_time); 
    }
}

void    ft_philos_atwork(t_philo *philo, t_info *info)
{
    pthread_t   print_thread;

    while (++philo->idx < info->tot_philos)
    {
        if (!ft_parse(&philo->args[philo->idx], info, philo))
            return ;
        if (pthread_create(&philo->philosophers[philo->idx], NULL, &ft_eating, (void *)&philo->args[philo->idx]))
            return ;
    }       
    philo->idx = -1;
    while (++philo->idx < info->tot_philos)
    {
       if (pthread_join(philo->philosophers[philo->idx], NULL))
        return ;
    }
    write(1, "here\n", 5);
    if (pthread_create(&print_thread, NULL, &ft_print_func, (void *)philo->args))
        return ;
    if (pthread_join(print_thread, NULL))
        return ;
    ft_free(philo->args, info);
    ft_destroy_mutexes(info);
}

