/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_msgs.c                                    :+:      :+:    :+:   */
/*   FIX: FIX THE EMAIL			              +:+ +:+         +:+     */
/*   By: uahmed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:44 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/02 17:27:47 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_fork_taken(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	pthread_mutex_lock(args->stop_lock);
	if (*args->philo_died)
	{
		pthread_mutex_unlock(args->stop_lock);
		return ;
	}
	pthread_mutex_unlock(args->stop_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d has taken a fork.\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_eating_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	if (*args->philo_died)
	{
		pthread_mutex_unlock(args->stop_lock);
		return ;
	}
	pthread_mutex_unlock(args->stop_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d is eating.\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_sleeping_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	pthread_mutex_lock(args->stop_lock);
	if (*args->philo_died)
	{
		pthread_mutex_unlock(args->stop_lock);
		return ;
	}
	pthread_mutex_unlock(args->stop_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d is sleeping.\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_thinking_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	pthread_mutex_lock(args->stop_lock);
	if (*args->philo_died)
	{
		pthread_mutex_unlock(args->stop_lock);
		return ;
	}
	pthread_mutex_unlock(args->stop_lock);
	pthread_mutex_lock(args->print_lock);
	printf("%d %d is thinking.\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}

void	ft_death_msg(t_args *args)
{
	int	time;

	time = (int)ft_current_time() - args->info->start_time;
	if (*args->philo_died)
		return ;
	pthread_mutex_lock(args->print_lock);
	printf("%d %d died.\n", time, *(args->phil_num));
	pthread_mutex_unlock(args->print_lock);
}
