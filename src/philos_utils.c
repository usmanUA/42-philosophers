/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:17:48 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 13:17:50 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

void	ft_eat(t_args *args, int time)
{
	ft_eating_msg(args, time);
	if (args->info->n_times_eat)
	{
		pthread_mutex_lock(args->meal_counter_lock);
		*args->meal_counter += 1;
		pthread_mutex_unlock(args->meal_counter_lock);
	}
	ft_wait(args->info->eating_time);
}

void	ft_sleep(t_args *args)
{
	ft_sleeping_msg(args);
	ft_wait(args->info->sleeping_time);
}

long	ft_current_time(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (time_val.tv_sec * 1000 + time_val.tv_usec / 1000);
}

void	ft_wait(long time)
{
	long	end;

	end = ft_current_time() + time;
	if (time > 10)
		usleep((time - 10) * 1000);
	while (ft_current_time() < end)
		usleep(1000);
}

void	ft_destroy_mutexes(t_info *info)
{
	int	ind;

	ind = -1;
	while (++ind < info->tot_philos)
		pthread_mutex_destroy(&info->fork[ind]);
	ind = -1;
	while (++ind < info->tot_philos)
		pthread_mutex_destroy(&info->eating_lock[ind]);
	ind = -1;
	while (++ind < info->tot_philos)
		pthread_mutex_destroy(&info->meal_counter_lock[ind]);
	pthread_mutex_destroy(&(info->print_lock));
	pthread_mutex_destroy(&(info->death_lock));
}
