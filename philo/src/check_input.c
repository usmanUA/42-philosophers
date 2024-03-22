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
    long res;
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
        if (res * 10 + (*num - '0') < res)
        {
            if (sign == -1)
                return (0);
            return (-1);
        }
        res += res * 10 + (*(num++) - '0');
    }
    return (res * sign);
}

void ft_save_args(t_data *data, int n_args, char **argv)
{
    data->tot_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->eating_time = ft_atoi(argv[3]);
    data->sleeping_time = ft_atoi(argv[4]);
    if (n_args == 5)
        data->n_times_eat = ft_atoi(argv[5]);
}
