/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:17:25 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 13:17:30 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\v' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\f')
		return (1);
	return (0);
}

static int	ft_atoi(const char *num)
{
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	while (ft_isspace(*num))
		num++;
	if (*num == '+' || *num == '-')
	{
		if (*(num++) == '-')
			sign *= -1;
	}
	if (*num == '+' || *num == '-')
		return (0);
	while (*num >= '0' && *num <= '9')
	{
		if (res * 10 + (*num - '0') < res)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		res = res * 10 + (*(num++) - '0');
	}
	return (res * sign);
}

int	ft_valid_args(int argc, char **argv, t_info *info)
{
	info->tot_philos = ft_atoi(argv[1]);
	if (info->tot_philos < 0)
		return (0);
	info->time_to_die = ft_atoi(argv[2]);
	if (info->time_to_die < 0)
		return (0);
	info->eating_time = ft_atoi(argv[3]);
	if (info->eating_time < 0)
		return (0);
	info->sleeping_time = ft_atoi(argv[4]);
	if (info->sleeping_time < 0)
		return (0);
	info->n_times_eat = 0;
	if (argc == 6)
		info->n_times_eat = ft_atoi(argv[5]);
	if (info->n_times_eat < 0)
		return (0);
	return (1);
}

void	ft_save_info(t_info *info)
{
	int				ind;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;

	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_init(&stop_lock, NULL);
	ind = -1;
	while (++ind < info->tot_philos)
		pthread_mutex_init(&info->eating_lock[ind], NULL);
	ind = -1;
	while (++ind < info->tot_philos)
		pthread_mutex_init(&info->meal_counter_lock[ind], NULL);
	ind = -1;
	while (++ind < info->tot_philos)
		pthread_mutex_init(&info->fork[ind], NULL);
	info->philo_died = 0;
	info->philo_full = 0;
	info->start_time = ft_current_time();
	info->print_lock = print_lock;
	info->stop_lock = stop_lock;
}

void	ft_philo_init(t_philo *philo)
{
	memset(philo->args, 0, sizeof(philo->args));
	memset(philo->phil_num, 0, sizeof(philo->phil_num));
	memset(philo->meal_counter, 0, sizeof(philo->meal_counter));
	memset(philo->have_eaten, 0, sizeof(philo->have_eaten));
	philo->idx = -1;
}
