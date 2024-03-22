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

void    ft_wait(int time)
{
    int start;
    int end;
    struct timeval time_val;

    gettimeofday(&time_val, NULL);
    start = time_val.tv_sec * 1000; 
    end = start + time;
    while (start < end)
    {
        usleep(10);
        gettimeofday(&time_val, NULL);
        start += time_val.tv_sec * 1000; 
    }
}

void *eating(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(philo->left_fork->fork_lock);
    ft_wait(philo->data->eating_time);
    pthread_mutex_unlock(philo->left_fork->fork_lock);
    pthread_mutex_lock(philo->right_fork->fork_lock);

    return (NULL);
}

int ft_forks_creation_failed(t_fork ***fork, int tot_philos)
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
            // free data
            return (1);
        }
        (*fork)[ind]->fork = ind;
        (*fork)[ind]->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
        if (!(*fork)[ind]->fork_lock)
        {
            // free data
            return (1);
        }
    }
    return (0);
}

int ft_parsing_failed(t_philo *philo, t_fork ***fork, t_data *data, int ind)
{
    philo->data = data;
    philo->phil_num = malloc(sizeof(int));
    if (!philo->phil_num)
    {
        // free data
        return (1);
    }
    *(philo->phil_num) = ind + 1;
    if (ind == 0)
        philo->left_fork = (*fork)[data->tot_philos];
    else
        philo->left_fork = (*fork)[ind-1];
    philo->right_fork = (*fork)[ind];
    return (0);
}

void    ft_philos_atwork(t_data *data)
{
    pthread_t philosopher[data->tot_philos];
    t_philo philo[data->tot_philos];
    t_fork  **fork;
    int i;
    
    i = -1;
    if (ft_forks_creation_failed(&fork, data->tot_philos))
        return ;
    while (++i < data->tot_philos)
    {
        if (ft_parsing_failed(&philo[i], &fork, data, i))
            return ;
       if (pthread_create((philosopher + i), NULL, &eating, (void *)&philo[i]))
        return ;
    }       
    i = -1;
    while (++i < data->tot_philos)
    {
       if (pthread_join(*(philosopher + i), NULL))
        return ;
    }
}

