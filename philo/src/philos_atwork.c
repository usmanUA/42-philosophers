/************************************************************************** */
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


void    ft_fork_taken(t_philo *philo)
{
    long long time;

    time = ft_current_time();
    pthread_mutex_lock(philo->print_lock);
    printf("%lld %d has taken a fork.\n", time, *(philo->phil_num));
    pthread_mutex_unlock(philo->print_lock);
}

void    ft_eating_msg(t_philo *philo)
{
    long long time;

    time = ft_current_time();
    pthread_mutex_lock(philo->print_lock);
    printf("%lld %d is eating.\n", time, *(philo->phil_num));
    pthread_mutex_unlock(philo->print_lock);
}

void    ft_sleeping_msg(t_philo *philo)
{
    long long time;

    time = ft_current_time();
    pthread_mutex_lock(philo->print_lock);
    printf("%lld %d is sleeping.\n", time, *(philo->phil_num));
    pthread_mutex_unlock(philo->print_lock);
}

void    ft_thinking_msg(t_philo *philo)
{
    long long time;

    time = ft_current_time();
    pthread_mutex_lock(philo->print_lock);
    printf("%lld %d is thinking.\n", time, *(philo->phil_num));
    pthread_mutex_unlock(philo->print_lock);
}


void    ft_death_msg(t_philo *philo)
{
    long long time;

    time = ft_current_time();
    pthread_mutex_lock(philo->print_lock);
    printf("%lld %d has died.\n", time, *(philo->phil_num));
    pthread_mutex_unlock(philo->print_lock);
}

void    ft_eat(t_philo *philo)
{
    ft_eating_msg(philo);
    ft_wait(philo->info->eating_time);
}

void    ft_sleep(t_philo *philo)
{
    ft_sleeping_msg(philo);
    ft_wait(philo->info->sleeping_time);
}

void    ft_think(t_philo *philo)
{
    ft_thinking_msg(philo);
}

void    ft_monitor_time(t_philo *philo, int *dead)
{
    if (philo->counter > philo->info->time_to_die)
    {
        ft_death_msg(philo);
        *dead = 1;
    }
}

void *ft_eating(void *arg)
{
    t_philo *philo;
    long long time;
    long long dying_time;
    long long locking_time;

    philo = (t_philo *)arg;
    while (1)
    {
        time = ft_current_time() - philo->info->start_time; 
        dying_time = time + philo->info->time_to_die; 
        pthread_mutex_lock(&philo->right_fork->fork_lock);
        ft_fork_taken(philo);
        pthread_mutex_lock(&philo->left_fork->fork_lock);
        ft_fork_taken(philo);
        ft_monitor_time(philo, &philo->info->dead);
        if (philo->info->dead)
            break ;
        ft_eat(philo);
        pthread_mutex_unlock(&philo->right_fork->fork_lock);
        pthread_mutex_unlock(&philo->left_fork->fork_lock);
        ft_sleep(philo);
        ft_think(philo);
        philo->info->start_time = ft_current_time();
    }
    return (NULL);
}

static void ft_parse(t_philo *philo, t_fork *fork, t_info *info, t_locks *locks)
{
    philo->info = info;
    philo->idx = info->idx+1;
    philo->phil_num = &philo->idx; 
    if (info->idx == 0)
        philo->left_fork = &fork[info->tot_philos-1];
    else
        philo->left_fork = &fork[info->idx-1];
    philo->right_fork = &fork[info->idx];
    philo->print_lock = &locks[0].print_lock;
    philo->start_lock = &locks[0].start_lock;
}

void    ft_init_mutexes(t_fork *fork, t_locks *locks, int tot_philos)
{
    int ind;

    ind = -1;
    while (++ind < tot_philos)
        pthread_mutex_init(&fork[ind].fork_lock, NULL);
    pthread_mutex_init(&(locks[0].print_lock), NULL);
    pthread_mutex_init(&(locks[0].start_lock), NULL);
}


void    ft_destroy_mutexes(t_fork *fork, t_locks *locks, int tot_philos)
{
    int ind;

    ind = -1;
    while (++ind < tot_philos)
        pthread_mutex_destroy(&fork[ind].fork_lock);
    pthread_mutex_destroy(&(locks[0].print_lock));
    pthread_mutex_destroy(&(locks[0].start_lock));
}


void    ft_philos_atwork(t_info *info)
{
    pthread_t philosopher[info->tot_philos];
    t_philo philo[info->tot_philos];
    t_fork  fork[info->tot_philos];
    t_locks locks[1];

    ft_init_mutexes(fork, locks, info->tot_philos); 
    while (++info->idx < info->tot_philos)
    {
        printf("index: %d\n", info->idx);
        ft_parse(&philo[info->idx], fork, info, locks);
        if (info->idx+1%2 == 0) 
        {
            write(1, "here\n", 5);
            ft_wait(10);
        }
        if (pthread_create((philosopher + info->idx), NULL, &ft_eating, (void *)&philo[info->idx]))
            return ;
    }       
    info->idx = -1;
    while (++info->idx < info->tot_philos)
    {
       if (pthread_join(*(philosopher + info->idx), NULL))
        return ;
    }
    ft_destroy_mutexes(fork, locks, info->tot_philos);
}

