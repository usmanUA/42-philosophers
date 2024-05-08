/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:04:20 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/08 09:04:21 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philo.h"

static	void	ft_init_monitor(t_monitor *mon)
{
	mon->ind = -1;
	memset(mon->last_meal_time, 0, sizeof(mon->last_meal_time));
	memset(mon->philos_full, NO, sizeof(mon->philos_full));
}

static int	ft_all_full(int *philos_full, int tot_philos)
{
	int	ind;

	ind = -1;
	while (++ind < tot_philos)
	{
		if (!philos_full[ind])
			return (NO);
	}
	return (YES);
}

static void	ft_check_meal_status(t_args *args, t_monitor *mon)
{
	pthread_mutex_lock(args->eating_lock);
	if (*args->have_eaten == YES)
	{
		*args->have_eaten = NO;
		pthread_mutex_unlock(args->eating_lock);
		mon->last_meal_time[mon->ind] = ft_current_time()
			- args->info->start_time;
		if (args->info->n_times_eat) //  NOTE: need to protect this variable using mutex?
		{
			pthread_mutex_lock(args->meal_counter_lock);
			if (*args->meal_counter >= args->info->n_times_eat)
				mon->philos_full[mon->ind] = YES;
			pthread_mutex_unlock(args->meal_counter_lock);
		}
	}
	pthread_mutex_unlock(args->eating_lock);
}

static int	ft_philo_dead_full(t_args *args, t_monitor *mon)
{
	// NOTE: args->info->start_time is read by multiple threads at the same time, lock it?
	if (ft_current_time() - args->info->start_time
		- mon->last_meal_time[mon->ind] >= args->info->time_to_die)
	{
		pthread_mutex_lock(args->death_lock);
		*args->philo_died = YES;
		pthread_mutex_unlock(args->death_lock);
		ft_death_msg(ft_current_time() - args->info->start_time, args);
		return (YES);
	}
	if (args->info->n_times_eat) // NOTE: read by multiple threads at the same time, lock it?
	{
		if (ft_all_full(mon->philos_full, args->info->tot_philos) == YES)
		{
			pthread_mutex_lock(args->death_lock);
			*args->philo_full = 1;
			pthread_mutex_unlock(args->death_lock);
			return (YES);
		}
	}
	return (NO);
}

void	ft_monitoring(t_philo *philo, t_info *info)
{
	t_monitor	mon;
	int		stop;

	ft_init_monitor(&mon);
	stop = NO;
	while (CONTINUE)
	{
		mon.ind = -1;
		usleep(1000);
		while (++mon.ind < info->tot_philos)
		{
			ft_check_meal_status(&philo->args[mon.ind], &mon);
			if (ft_philo_dead_full(&philo->args[mon.ind], &mon) == YES)
			{
				stop = YES;
				break ;
			}
		}
		if (stop == YES)
			break ;
	}
}

