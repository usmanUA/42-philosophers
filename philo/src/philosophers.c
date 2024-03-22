/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:03:10 by uahmed            #+#    #+#             */
/*   Updated: 2024/03/22 14:31:41 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc == 5 || argc == 6)
	{
		ft_save_args(&data, argc-1, argv);
		ft_philos_atwork(&data);
		return (0);
	}
	printf("Error.\n\nUsage: \n");
	printf("\t    ./philo\n");
	printf("\t    number_of_philosophers.\n");
	printf("\t    time_to_die (in milliseconds).\n");
	printf("\t    time_to_eat (in milliseconds).\n");
	printf("\t    time_to_sleep (in milliseconds).\n");
	printf("--Optional  [number_of_times_each_philosopher_must_eat]\n\n");
	return (0);
}
