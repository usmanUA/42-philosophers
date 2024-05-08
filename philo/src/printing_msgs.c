/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_msgs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:33:11 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 11:33:14 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

void	ft_fork_taken(t_args *args, int time)
{
	pthread_mutex_lock(args->death_lock);
	if (*args->philo_died == YES)
	{
		pthread_mutex_unlock(args->death_lock);
		return ;
	}
	pthread_mutex_unlock(args->death_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d has taken a fork\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_eating_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	pthread_mutex_lock(args->death_lock);
	if (*args->philo_died == YES)
	{
		pthread_mutex_unlock(args->death_lock);
		return ;
	}
	pthread_mutex_unlock(args->death_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d is eating\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_sleeping_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	pthread_mutex_lock(args->death_lock);
	if (*args->philo_died == YES)
	{
		pthread_mutex_unlock(args->death_lock);
		return ;
	}
	pthread_mutex_unlock(args->death_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d is sleeping\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_thinking_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	pthread_mutex_lock(args->death_lock);
	if (*args->philo_died == YES)
	{
		pthread_mutex_unlock(args->death_lock);
		return ;
	}
	pthread_mutex_unlock(args->death_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d is thinking\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_death_msg(int time, t_args *args)
{
	pthread_mutex_lock(args->print_lock);
	printf("\033[1;31m%d %d died\033[0m\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}
