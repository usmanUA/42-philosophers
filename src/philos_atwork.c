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

static int	ft_stop_simulation(t_args *args, int unlock)
{
	pthread_mutex_lock(args->death_lock);
	if (*args->philo_died == YES || (args->info->n_times_eat
			&& *args->philo_full == YES))
	{
		pthread_mutex_unlock(args->death_lock);
		if (unlock == YES)
		{
			pthread_mutex_unlock(args->left_fork);
		}
		return (YES);
	}
	pthread_mutex_unlock(args->death_lock);
	return (NO);
}

static void	ft_parse(t_args *args, t_info *info, t_philo *philo)
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
	args->death_lock = &info->death_lock;
	args->eating_lock = &info->eating_lock[philo->idx];
	args->meal_counter_lock = &info->meal_counter_lock[philo->idx];
}

static int	ft_eat_sleep_repeat(t_args *args)
{
	int	time;

	pthread_mutex_lock(args->left_fork);
	ft_fork_taken(args, ft_current_time() - args->info->start_time);
	if (ft_stop_simulation(args, YES) == YES)
		return (STOP);
	pthread_mutex_lock(args->right_fork);
	pthread_mutex_lock(args->eating_lock);
	*args->have_eaten = YES;
	pthread_mutex_unlock(args->eating_lock);
	time = (int)ft_current_time() - args->info->start_time;
	ft_eat(args, time);
	pthread_mutex_unlock(args->left_fork);
	pthread_mutex_unlock(args->right_fork);
	ft_sleep(args);
	if (ft_stop_simulation(args, NO) == YES)
		return (STOP);
	ft_thinking_msg(args);
	return (DONT);
}

static void	*ft_eating(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	if (args->info->tot_philos == 1)
	{
		pthread_mutex_lock(args->left_fork);
		ft_fork_taken(args, ft_current_time() - args->info->start_time);
		ft_wait(args->info->time_to_die);
		ft_death_msg(ft_current_time() - args->info->start_time, args);
		pthread_mutex_unlock(args->left_fork);
		return (NULL);
	}
	if (*(args->phil_num) % 2 == 0)
		usleep(7000);
	if (args->info->tot_philos % 2 == 1
		&& *args->phil_num == args->info->tot_philos)
		usleep(6000);
	while (CONTINUE)
	{
		if (ft_eat_sleep_repeat(args) == STOP)
			break ;
	}
	return (NULL);
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
