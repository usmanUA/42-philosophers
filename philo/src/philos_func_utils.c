/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
//	FIX: FIX THE EMAIL  
/*   By: uahmed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:28:11 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/02 17:28:14 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_eat(t_args *args)
{
	ft_eating_msg(args);
	*args->meal_counter += 1;
	ft_wait(args->info->eating_time);
}

void	ft_sleep(t_args *args)
{
	ft_sleeping_msg(args);
	ft_wait(args->info->sleeping_time);
}

void	ft_think(t_args *args)
{
	ft_thinking_msg(args);
}
