/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:02:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 14:19:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long ft_current_time()
{
    struct timeval time_val;

    gettimeofday(&time_val, NULL);
    return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
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

