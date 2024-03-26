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
static long long ft_atoll(const char *num)
{
    long long   res;
    long long sign;

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

int ft_save_args(t_info *info, int n_args, char **argv)
{
    info->idx = -1;
    info->dead = 0;
    info->tot_philos = ft_atoll(argv[1]);
    info->time_to_die = ft_atoll(argv[2]);
    info->eating_time = ft_atoll(argv[3]);
    info->sleeping_time = ft_atoll(argv[4]);
    info->philo_died = 0; 
    info->start_time = ft_current_time(); 
    if (n_args == 5)
        info->n_times_eat = ft_atoll(argv[5]);
    return (0);
}
