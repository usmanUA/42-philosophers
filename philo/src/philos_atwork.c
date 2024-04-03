/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_atwork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:24:37 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 15:11:46 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	ft_monitor_time(t_args *args, int wait)
{
	if (*args->start)
	{
		*args->start = 0;
		*args->start_counter = ft_current_time() - args->info->start_time;
		if (*args->start_counter < args->info->time_to_die)
			return ;
	}
	else
	{
		if (wait)
			ft_wait(args->info->last_meal);
		*args->time_counter = ft_current_time() - *args->current_time;
		if (*args->time_counter < args->info->time_to_die)
			return ;
	}
	if (!*args->philo_died)
		ft_death_msg(args);
	args->info->philo_died = 1;
}

static int	ft_stop_simulation(t_args *args, int wait, int unlock)
{
	pthread_mutex_lock(args->stop_lock);
	ft_monitor_time(args, wait);
	if (*args->philo_died || (args->info->n_times_eat
			&& *args->meal_counter >= args->info->n_times_eat))
	{
		if (unlock)
		{
			pthread_mutex_unlock(args->left_fork);
			pthread_mutex_unlock(args->right_fork);
		}
		pthread_mutex_unlock(args->stop_lock);
		return (1);
	}
	pthread_mutex_unlock(args->stop_lock);
	return (0);
}

// static int	ft_eat_sleep_repeat(t_args *args)
// {
// 	pthread_mutex_lock(args->left_fork);
// 	ft_fork_taken(args);
// 	pthread_mutex_lock(args->right_fork);
// 	ft_fork_taken(args);
// 	if (ft_stop_simulation(args, 0, 1))
// 		return (0);
// 	*args->current_time = ft_current_time();
// 	ft_eat(args);
// 	pthread_mutex_unlock(args->left_fork);
// 	pthread_mutex_unlock(args->right_fork);
// 	if (ft_stop_simulation(args, 0, 0))
// 		return (0);
// 	ft_sleep(args);
// 	if (ft_stop_simulation(args, 0, 0))
// 		return (0);
// 	ft_think(args);
// 	if (ft_stop_simulation(args, 1, 0))
// 		return (0);
// 	return (1);
// }

static void	*ft_eating(void *arg)
{
	t_args	*args;

	args = (t_args *)arg;
	if (*args->phil_num == 2 || *args->phil_num == 4)
		printf("TIME for %d: %ld\n", *args->phil_num, ft_current_time() - args->info->start_time);
	if (*args->phil_num == 3 || *args->phil_num == 1)
		printf("TIME for %d: %ld\n", *args->phil_num, ft_current_time() - args->info->start_time);
	if (args->info->tot_philos == 1)
	{
		pthread_mutex_lock(args->left_fork);
		ft_wait(args->info->time_to_die);
		ft_death_msg(args);
		pthread_mutex_unlock(args->left_fork);
		return (NULL);
	}
	if (*(args->phil_num) % 2 == 0)
		ft_wait(10);
	while (1)
	{
		pthread_mutex_lock(args->left_fork);
		ft_fork_taken(args);
		pthread_mutex_lock(args->right_fork);
		ft_fork_taken(args);
		if (ft_stop_simulation(args, 0, 1))
			break ;
		*args->current_time = ft_current_time();
		ft_eat(args);
		pthread_mutex_unlock(args->left_fork);
		pthread_mutex_unlock(args->right_fork);
		if (ft_stop_simulation(args, 0, 0))
			break ;	
		ft_sleep(args);
		if (ft_stop_simulation(args, 0, 0))
			break ;
		ft_think(args);
		if (ft_stop_simulation(args, 1, 0))
			break ;
	}
	return (NULL);
}

void	ft_philos_atwork(t_philo *philo, t_info *info)
{
	while (++philo->idx < info->tot_philos)
	{
		ft_parse(&philo->args[philo->idx], info, philo);
		if (pthread_create(&philo->philosophers[philo->idx], NULL, &ft_eating, (void *)&philo->args[philo->idx]))
			return ;
	}
	philo->idx = -1;
	while (++philo->idx < info->tot_philos)
	{
		if (pthread_join(philo->philosophers[philo->idx], NULL))
			return ;
	}
	ft_destroy_mutexes(info);
}
