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
        *args->left_fork_taken = 1;
        pthread_mutex_lock(args->right_fork);
        *args->right_fork_taken = 1;
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
    t_args *args;
    int ind;

    args = (t_args *)arg;
    ind = -1;
    while (1)
    {
        ind = -1;
        while (++ind < args[0].info->tot_philos)
        {
            if (*args[ind].left_fork_taken)
            {
                ft_fork_msg(&args[ind]);
                *args[ind].left_fork_taken = 0;
            }
            if (*args[ind].right_fork_taken)
            {
                ft_fork_msg(&args[ind]);
                *args[ind].right_fork_taken = 0;
            }
            if (*args[ind].eaten)
            {
                ft_eating_msg(&args[ind]);
                *args[ind].eaten = 0;
            }
            if (*args[ind].slept)
            {
                ft_sleeping_msg(&args[ind]);
                *args[ind].slept = 0;
            }
            if (*args[ind].thought)
            {
                ft_thinking_msg(&args[ind]);
                *args[ind].thought = 0;
            }
            if (*args[ind].died)
            {
                ft_death_msg(&args[ind]);
                *args[ind].died = 0;
                break ;
            }
        }
    }
    return (NULL);
}

void    ft_parse_again(t_philo *philo, t_info *info)
{
    int ind;
    ind = -1;
    while (++ind < info->tot_philos)
    {
        philo->args[ind].info = info;
        philo->phil_num[philo->idx] = philo->idx+1; 
        philo->args[ind].phil_num = &philo->phil_num[philo->idx]; 
        philo->args[ind].time_counter = &philo->time_counter[philo->idx]; 
        philo->args[ind].meal_counter = &philo->meal_counter[philo->idx]; 
        philo->args[ind].start_counter = &philo->start_counter[philo->idx]; 
        philo->args[ind].start = &philo->start[philo->idx]; 
        philo->args[ind].current_time= &philo->current_time[philo->idx]; 
        philo->args[ind].philo_died = &info->philo_died;
        if (philo->idx == 0)
            philo->args[ind].right_fork = &info->fork[info->tot_philos-1];
        else
            philo->args[ind].right_fork = &info->fork[philo->idx-1];
        philo->args[ind].left_fork = &info->fork[philo->idx];
        philo->args[ind].print_lock= &info->print_lock;
        philo->args[ind].stop_lock= &info->stop_lock;
        philo->args[ind].left_fork_taken = &info->left_fork_taken;
        philo->args[ind].right_fork_taken = &info->right_fork_taken;
        philo->args[ind].eaten = &info->eaten;
        philo->args[ind].slept = &info->slept;
        philo->args[ind].thought = &info->thought;
        philo->args[ind].died = &info->died;
    }

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
    ft_parse_again(philo, info);
    printf("tot_philos %d coming directly from info\n", info->tot_philos);
    printf("tot_philos %d coming indirectly from info\n", philo->args[0].info->tot_philos);
    write(1, "here\n", 5);
    if (pthread_create(&print_thread, NULL, &ft_print_func, (void *)philo->args))
        return ;
    if (pthread_join(print_thread, NULL))
        return ;
    ft_destroy_mutexes(info);
}

