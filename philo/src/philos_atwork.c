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

void    ft_freedata(t_locks **locks, t_fork ***fork, int index)
{
    int ind;

    ind = -1;
    if (locks)
    {
        if ((*locks)->print_lock)
            free((*locks)->print_lock);
        if ((*locks)->start_lock)
            free((*locks)->start_lock);
        free(*locks);
    }
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
    struct timeval time_val;

    gettimeofday(&time_val, NULL);
    start = time_val.tv_sec * 1000 + time_val.tv_usec / 1000; 
    end = start + time;
    while (start < end)
    {
        usleep(10);
        gettimeofday(&time_val, NULL);
        start += time_val.tv_sec * 1000 + time_val.tv_usec / 1000; 
    }
}

void *eating(void *arg)
{
    t_philo *philo;
    long long start;
    long long end;
    long long current;
    struct timeval time_val;

    philo = (t_philo *)arg;
    // pthread_mutex_lock(philo->locks->start_lock);
    while (1)
    {
        gettimeofday(&time_val, NULL);
        start = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
        end = start + philo->data->time_to_die; 
        pthread_mutex_lock(philo->right_fork->fork_lock);
        pthread_mutex_lock(philo->left_fork->fork_lock);
        gettimeofday(&time_val, NULL);
        current = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
        if (current >= end)
        {
            printf("Philosopher %d has died", *(philo->phil_num));
            break ;
        }
        printf("Philospher %d has taken the fork.\n", *(philo->phil_num));
        printf("Philospher %d is eating.\n", *(philo->phil_num));
        ft_wait(philo->data->eating_time);
        pthread_mutex_unlock(philo->right_fork->fork_lock);
        pthread_mutex_unlock(philo->left_fork->fork_lock);
        printf("Philospher %d is sleeping.\n", *(philo->phil_num));
        ft_wait(philo->data->sleeping_time);
        printf("Philospher %d is thinking.\n", *(philo->phil_num));
        printf("still going.\n");
    }
    // pthread_mutex_unlock(philo->locks->start_lock);
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
            ft_freedata(NULL, fork, ind);
            return (1);
        }
        (*fork)[ind]->fork = ind;
        (*fork)[ind]->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        if (!(*fork)[ind]->fork_lock)
        {
            ft_freedata(NULL, fork, ind);
            return (1);
        }
    }
    return (0);
}

// ***** Create Forks, their locks and also print lock, start lock *****
int ft_forks_locks_creation_failed(t_fork ***fork, int tot_philos, t_locks **locks)
{
    if (ft_create_forks(fork, tot_philos))
        return (1);
    *locks = (t_locks *)malloc(sizeof(t_locks));
    if (!(*locks))
    {
        ft_freedata(NULL, fork, tot_philos); 
        return (1);
    }
    (*locks)->print_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!(*locks)->print_lock) 
    {
        ft_freedata(locks, fork, tot_philos);
        return (1);
    }
    (*locks)->start_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!(*locks)->start_lock) 
    {
        ft_freedata(locks, fork, tot_philos);
        return (1);
    }
    return (0);
}

int ft_parsing_failed(t_philo *philo, t_fork ***fork, t_data *data, t_locks **locks)
{
    philo->data = data;
    philo->phil_num = malloc(sizeof(int));
    if (!philo->phil_num)
    {
        ft_freedata(NULL, fork, data->tot_philos);
        return (1);
    }
    *(philo->phil_num) = data->idx + 1;
    if (data->idx == 0)
        philo->left_fork = (*fork)[data->tot_philos-1];
    else
        philo->left_fork = (*fork)[data->idx-1];
    philo->right_fork = (*fork)[data->idx];
    philo->locks = *locks;
    return (0);
}

void    ft_init_mutexes(t_fork ***fork, t_locks **locks)
{
    int ind;

    ind = -1;
    while ((*fork)[++ind])
        pthread_mutex_init((*fork)[ind]->fork_lock, NULL);
    pthread_mutex_init((*locks)->print_lock, NULL);
    pthread_mutex_init((*locks)->start_lock, NULL);
}

void    ft_destroy_mutexes(t_fork ***fork, t_locks **locks)
{
    int ind;

    ind = -1;
    while ((*fork)[++ind])
        pthread_mutex_destroy((*fork)[ind]->fork_lock);
    pthread_mutex_destroy((*locks)->print_lock);
    pthread_mutex_destroy((*locks)->start_lock);
}


void    ft_philos_atwork(t_data *data)
{
    pthread_t philosopher[data->tot_philos];
    t_philo philo[data->tot_philos];
    t_fork  **fork;
    t_locks *locks;

    //write(1, "here\n", 5);
    if (ft_forks_locks_creation_failed(&fork, data->tot_philos, &locks))
        return ;
    ft_init_mutexes(&fork, &locks); 
//    pthread_mutex_lock(locks->start_lock);
    while (++data->idx < data->tot_philos)
    {
        if (ft_parsing_failed(&philo[data->idx], &fork, data, &locks))
            return ;
       if (pthread_create((philosopher + data->idx), NULL, &eating, (void *)&philo[data->idx]))
        return ;
    }       
    // pthread_mutex_unlock(locks->start_lock);
    data->idx = -1;
    while (++data->idx < data->tot_philos)
    {
       if (pthread_join(*(philosopher + data->idx), NULL))
        return ;
    }
    ft_destroy_mutexes(&fork, &locks);
    ft_freedata(&locks, &fork, data->tot_philos);
}

