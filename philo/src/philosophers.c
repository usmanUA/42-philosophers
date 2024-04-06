/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:19:59 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 13:20:01 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo	philo;
	t_info	info;

	if ((argc == 5 || argc == 6) && ft_valid_args(argc, argv, &info))
	{
		ft_save_info(&info);
		ft_philo_init(&philo);
		ft_philos_atwork(&philo, &info);
		return (0);
	}
	printf("Error.\n\nUsage: \n");
	printf("\t    ./philo\n");
	printf("\t    (+)number_of_philosophers.\n");
	printf("\t    (+)time_to_die (in milliseconds).\n");
	printf("\t    (+)time_to_eat (in milliseconds).\n");
	printf("\t    (+)time_to_sleep (in milliseconds).\n");
	printf("--Optional  (+)[number_of_times_each_philosopher_must_eat]\n\n");
	return (0);
}
