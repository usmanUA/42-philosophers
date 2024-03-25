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

long long ft_current_time()
{
    struct timeval time_val;

    gettimeofday(&time_val, NULL);
    return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

void    ft_freeinfo(t_locks **locks, t_fork ***fork, int index)
{
    int ind;

    ind = -1;
    if (fork)
    {
        while (++ind < index)
        {
            if ((*fork)[ind])
            {
                if ((*fork)[ind]->fork_lock)
                    free((*fork)[ind]->fork_lock);
                free((*fork)[ind]);
            }
        }
    }
}

void    ft_wait(long long time)
{
    long long start;
    long long end;

    start = ft_current_time(); 
    end = start + time;
    while (start < end)
    {
        usleep(10);
        start += ft_current_time(); 
    }
}

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

void *ft_think_first(void *arg)
{
    t_philo *philo;
    long long start;
    long long end;
    long long current;

    philo = (t_philo *)arg;
    while (1)
    {
        start = ft_current_time(); 
        end = start + philo->info->time_to_die; 
        pthread_mutex_lock(philo->right_fork->fork_lock);
        ft_fork_taken(philo);
        pthread_mutex_lock(philo->left_fork->fork_lock);
        ft_fork_taken(philo);
        current = ft_current_time(); 
        if (current >= end)
        {
            ft_death_msg(philo); 
            break ;
        }
        ft_eat(philo);
        pthread_mutex_unlock(philo->right_fork->fork_lock);
        pthread_mutex_unlock(philo->left_fork->fork_lock);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}

void *ft_eat_first(void *arg)
{
    t_philo *philo;
    long long start;
    long long end;
    long long current;

    philo = (t_philo *)arg;
    while (1)
    {
        start = ft_current_time(); 
        end = start + philo->info->time_to_die; 
        pthread_mutex_lock(philo->right_fork->fork_lock);
        ft_fork_taken(philo);
        pthread_mutex_lock(philo->left_fork->fork_lock);
        ft_fork_taken(philo);
        current = ft_current_time(); 
        if (current >= end)
        {
            ft_death_msg(philo); 
            break ;
        }
        ft_eat(philo);
        pthread_mutex_unlock(philo->right_fork->fork_lock);
        pthread_mutex_unlock(philo->left_fork->fork_lock);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}

static int ft_create_forks(t_fork ***fork, int tot_philos)
{
    int ind;

    ind = -1;
    *fork = (t_fork **)malloc(tot_philos * sizeof(t_fork *));
    if (!(*fork))
        return (1);
    while (++ind < tot_philos)
    {
        (*fork)[ind] = (t_fork *)malloc(sizeof(t_fork));
        if (!(*fork)[ind])
        {
            ft_freeinfo(NULL, fork, ind);
            return (1);
        }
        (*fork)[ind]->fork = ind;
        (*fork)[ind]->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        if (!(*fork)[ind]->fork_lock)
        {
            ft_freeinfo(NULL, fork, ind);
            return (1);
        }
    }
    return (0);
}

// ***** Create Forks, their locks and also print lock, start lock *****
static int ft_forks_locks_creation_failed(t_fork ***fork, int tot_philos, t_locks **locks)
{
    if (ft_create_forks(fork, tot_philos))
        return (1);
    return (0);
}

static int ft_parsing_failed(t_philo *philo, t_fork ***fork, t_info *info, t_locks *locks)
{
    philo->info = info;
    philo->phil_num = malloc(sizeof(int));
    if (!philo->phil_num)
    {
        ft_freeinfo(NULL, fork, info->tot_philos);
        return (1);
    }
    *(philo->phil_num) = info->idx + 1;
    if (info->idx == 0)
        philo->left_fork = (*fork)[info->tot_philos-1];
    else
        philo->left_fork = (*fork)[info->idx-1];
    philo->right_fork = (*fork)[info->idx];
    philo->print_lock = &(locks->print_lock);
    return (0);
}

void    ft_init_mutexes(t_fork ***fork, t_locks *locks, int tot_philos)
{
    int ind;

    ind = -1;
    while (++ind < tot_philos)
        pthread_mutex_init((*fork)[ind]->fork_lock, NULL);
    pthread_mutex_destroy(&(locks->print_lock));
    pthread_mutex_destroy(&(locks->start_lock));
}

void    ft_destroy_mutexes(t_fork ***fork, t_locks *locks, int tot_philos)
{
    int ind;

    ind = -1;
    while (++ind < tot_philos)
        pthread_mutex_destroy((*fork)[ind]->fork_lock);
    pthread_mutex_destroy(&(locks->print_lock));
    pthread_mutex_destroy(&(locks->start_lock));
}


void    ft_philos_atwork(t_info *info)
{
    pthread_t philosopher[info->tot_philos];
    t_philo philo[info->tot_philos];
    t_fork  **fork;
    t_locks *locks;

    if (ft_forks_locks_creation_failed(&fork, info->tot_philos, &locks))
        return ;
    ft_init_mutexes(&fork, locks, info->tot_philos); 
    while (++info->idx < info->tot_philos+1)
    {
        if (ft_parsing_failed(&philo[info->idx], &fork, info, locks))
            return ;
        if (info->idx%2 == 1) 
            ft_wait(10);
        if (pthread_create((philosopher + info->idx), NULL, &ft_eat_first, (void *)&philo[info->idx]))
            return ;
    }       
    info->idx = -1;
    while (++info->idx < info->tot_philos)
    {
       if (pthread_join(*(philosopher + info->idx), NULL))
        return ;
    }
    ft_destroy_mutexes(&fork, locks, info->tot_philos);
    ft_freeinfo(&locks, &fork, info->tot_philos);
}

