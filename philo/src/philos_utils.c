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
	while (ft_current_time() < end)
		usleep(500);
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
	pthread_mutex_destroy(&(info->stop_lock));
}

void	ft_parse(t_args *args, t_info *info, t_philo *philo)
{
	args->info = info;
	philo->phil_num[philo->idx] = philo->idx + 1;
	args->phil_num = &philo->phil_num[philo->idx];
	args->philo_died = &info->philo_died;
	args->philo_full = &info->philo_full;
	args->meal_counter = &philo->meal_counter[philo->idx];
	args->have_eaten = &philo->have_eaten[philo->idx];
	if (philo->idx == 0)
		args->right_fork = &info->fork[info->tot_philos - 1];
	else
		args->right_fork = &info->fork[philo->idx - 1];
	args->left_fork = &info->fork[philo->idx];
	args->print_lock = &info->print_lock;
	args->stop_lock = &info->stop_lock;
	args->eating_lock = &info->eating_lock[philo->idx];
	args->meal_counter_lock = &info->meal_counter_lock[philo->idx];
}

void	ft_check_meal_status(t_args *args, t_monitor *mon)
{
	pthread_mutex_lock(args->eating_lock);
	if (*args->have_eaten)
	{
		*args->have_eaten = 0;
		mon->last_meal_time[mon->ind] = ft_current_time()
			- args->info->start_time;
		if (args->info->n_times_eat)
		{
			pthread_mutex_lock(args->meal_counter_lock);
			if (*args->meal_counter >= args->info->n_times_eat)
				mon->philos_full[mon->ind] = 1;
			pthread_mutex_unlock(args->meal_counter_lock);
		}
	}
	pthread_mutex_unlock(args->eating_lock);
}
