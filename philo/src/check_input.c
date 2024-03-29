/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:12:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 14:36:27 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int ft_isdigit(const char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int ft_isspace(const char c)
{
    if (c == ' ' || c == '\v' || c == '\t' || c == '\n' || c == '\r' || c == '\f')
        return (1);
    return (0);
}
static int ft_atoi(const char *num)
{
    long   res;
    int sign;

    sign = 1;
    res = 0;
    while (ft_isspace(*num))
        num++;
    if (*num == '+' || *num == '-')
    {
        if (*(num++) == '-')
            sign *= -1;
    }
    if (*num == '+' || *num == '-')
        return (0);
    while (ft_isdigit(*num))
    {
        res *= 10;
        res += (*(num++) - '0');
    }
    return (res * sign);
}

void    ft_save_info(t_info *info, int argc, char **argv)
{
    pthread_mutex_t print_lock;
    pthread_mutex_t stop_lock;
    int eat_sleep;

    pthread_mutex_init(&print_lock, NULL);
    pthread_mutex_init(&stop_lock, NULL);
    info->tot_philos = ft_atoi(argv[1]);
    info->time_to_die = ft_atoi(argv[2]);
    info->eating_time = ft_atoi(argv[3]);
    info->sleeping_time = ft_atoi(argv[4]);
    eat_sleep = info->eating_time+info->sleeping_time;
    info->last_eat = info->time_to_die - eat_sleep; 
    if (info->last_eat <= 0)
        info->last_eat = 0;
    if (argc == 6)
        info->n_times_eat = ft_atoi(argv[5]);
    info->philo_died = 0; 
    info->start_time = ft_current_time(); 
    info->print_lock = print_lock;
    info->stop_lock = stop_lock;
    ft_init_forks(info);
}

void    ft_philo_init(t_philo *philo)
{
    memset(philo->args, 0, sizeof(philo->args));
    memset(philo->phil_num, 0, sizeof(philo->phil_num));
    memset(philo->counter, 0, sizeof(philo->counter));
    memset(philo->start_counter, 0, sizeof(philo->start_counter));
    memset(philo->start, 1, sizeof(philo->start));
    memset(philo->current_time, 1, sizeof(philo->current_time));
    philo->idx = -1;
}

