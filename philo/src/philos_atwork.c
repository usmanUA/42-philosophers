/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_atwork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:17:07 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 13:17:10 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_eat_sleep_repeat(t_args *args)
{
	if (args->info->tot_philos % 2 == 1
		&& (*args->phil_num == args->info->tot_philos || *args->phil_num
			- 1 == args->info->tot_philos))
		usleep(6000);
	pthread_mutex_lock(args->left_fork);
	ft_fork_taken(args, (int)ft_current_time() - args->info->start_time);
	pthread_mutex_lock(args->right_fork);
	ft_fork_taken(args, (int)ft_current_time() - args->info->start_time);
	if (ft_stop_simulation(args, 1))
		return (0);
	pthread_mutex_lock(args->eating_lock);
	*args->have_eaten = 1;
	pthread_mutex_unlock(args->eating_lock);
	ft_eat(args);
	pthread_mutex_unlock(args->left_fork);
	pthread_mutex_unlock(args->right_fork);
	if (ft_stop_simulation(args, 0))
		return (0);
	ft_sleep(args);
	if (ft_stop_simulation(args, 0))
		return (0);
	ft_thinking_msg(args);
	if (ft_stop_simulation(args, 0))
		return (0);
	return (1);
}

static void	*ft_eating(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	ft_thinking_msg(args);
	if (args->info->tot_philos == 1)
	{
		pthread_mutex_lock(args->left_fork);
		ft_fork_taken(args, (int)ft_current_time() - args->info->start_time);
		ft_wait(args->info->time_to_die);
		ft_death_msg(ft_current_time() - args->info->start_time, args);
		pthread_mutex_unlock(args->left_fork);
		return (NULL);
	}
	if (*(args->phil_num) % 2 == 0)
		usleep(3000);
	while (1)
	{
		if (!ft_eat_sleep_repeat(args))
			break ;
	}
	return (NULL);
}

static int	ft_philo_dead_full(t_args *args, t_monitor *mon)
{
	if (ft_current_time() - args->info->start_time
		- mon->last_meal_time[mon->ind] >= args->info->time_to_die)
	{
		ft_death_msg(ft_current_time() - args->info->start_time, args);
		pthread_mutex_lock(args->stop_lock);
		*args->philo_died = 1;
		pthread_mutex_unlock(args->stop_lock);
		return (1);
	}
	if (args->info->n_times_eat && ft_all_full(mon->philos_full,
			args->info->tot_philos))
	{
		mon->all_full = 1;
		return (1);
	}
	return (0);
}

static void	ft_monitoring(t_philo *philo, t_info *info)
{
	t_monitor	mon;

	ft_init_monitor(&mon);
	while (42)
	{
		mon.ind = -1;
		usleep(900);
		while (++mon.ind < info->tot_philos)
		{
			ft_check_meal_status(&philo->args[mon.ind], &mon);
			if (ft_philo_dead_full(&philo->args[mon.ind], &mon))
				break ;
		}
		pthread_mutex_lock(&info->stop_lock);
		if (info->philo_died || mon.all_full)
		{
			if (mon.all_full)
				info->philo_full = 1;
			pthread_mutex_unlock(&info->stop_lock);
			break ;
		}
		pthread_mutex_unlock(&info->stop_lock);
	}
}

void	ft_philos_atwork(t_philo *philo, t_info *info)
{
	while (++philo->idx < info->tot_philos)
	{
		ft_parse(&philo->args[philo->idx], info, philo);
		if (pthread_create(&philo->philosophers[philo->idx], NULL, &ft_eating,
				(void *)&philo->args[philo->idx]))
			return ;
	}
	if (info->tot_philos > 1)
		ft_monitoring(philo, info);
	philo->idx = -1;
	while (++philo->idx < info->tot_philos)
	{
		if (pthread_join(philo->philosophers[philo->idx], NULL))
			return ;
	}
	ft_destroy_mutexes(info);
}
