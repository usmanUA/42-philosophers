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

long ft_current_time()
{
    struct timeval time_val;

    gettimeofday(&time_val, NULL);
    return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

void    ft_wait(long time)
{
    long end;

    ft_current_time(); 
    end = ft_current_time() + time; 
    while (ft_current_time() < end)
        usleep(10);
}

