/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_func_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:32:53 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 11:32:57 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_eat(t_args *args)
{
	ft_eating_msg(args);
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

void	ft_init_monitor(t_monitor *mon)
{
	mon->ind = -1;
	memset(mon->last_meal_time, 0, sizeof(mon->last_meal_time));
	memset(mon->philos_full, 0, sizeof(mon->philos_full));
	mon->all_full = 0;
}

int	ft_all_full(int *philos_full, int tot_philos)
{
	int	ind;

	ind = -1;
	while (++ind < tot_philos)
	{
		if (!philos_full[ind])
			return (0);
	}
	return (1);
}

int	ft_stop_simulation(t_args *args, int unlock)
{
	pthread_mutex_lock(args->stop_lock);
	if (*args->philo_died || (args->info->n_times_eat && *args->philo_full))
	{
		pthread_mutex_unlock(args->stop_lock);
		if (unlock)
		{
			pthread_mutex_unlock(args->left_fork);
			pthread_mutex_unlock(args->right_fork);
		}
		return (1);
	}
	pthread_mutex_unlock(args->stop_lock);
	return (0);
}
