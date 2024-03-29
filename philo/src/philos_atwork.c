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
        ft_fork_taken(args);
        pthread_mutex_lock(args->right_fork);
        ft_fork_taken(args);
        if (ft_stop_simulation(args, 0, 1))
            break ;
        *args->current_time = ft_current_time();
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

    return (NULL);
}

void    ft_philos_atwork(t_philo *philo, t_info *info)
{
    pthread_t   print_thread;

    while (++philo->idx < info->tot_philos)
    {
        ft_parse(&philo->args[philo->idx], info, philo);
        if (pthread_create(&philo->philosophers[philo->idx], NULL, &ft_eating, (void *)&philo->args[philo->idx]))
            return ;
    }       
    philo->idx = -1;
    while (++philo->idx < info->tot_philos)
    {
       if (pthread_join(philo->philosophers[philo->idx], NULL))
        return ;
    }
    philo->args[philo->idx].info = info;
    if (pthread_create(&print_thread, NULL, &ft_print_func, (void *)&philo->args[philo->idx]))
        return ;
    if (pthread_join(print_thread, NULL))
        return ;
    ft_destroy_mutexes(info);
}

