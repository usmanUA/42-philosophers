/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:18:10 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/03 13:18:14 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stdio.h"
# include "string.h"
# include "sys/time.h"
# include "unistd.h"

typedef enum	s_flags
{
	STOP,
	DONT,
	YES,
	NO,
	CONTINUE = 42,
}	t_flags;

typedef struct s_monitor
{
	int				ind;
	long			last_meal_time[200];
	int				philos_full[200];
}					t_monitor;

typedef struct s_info
{
	int				tot_philos;
	int				time_to_die;
	int				eating_time;
	int				sleeping_time;
	int				n_times_eat;
	int				philo_died;
	int				philo_full;
	long			start_time;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	meal_counter_lock[200];
	pthread_mutex_t	eating_lock[200];
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}					t_info;

typedef struct s_args
{
	int				*meal_counter;
	int				*have_eaten;
	int				*phil_num;
	int				*philo_died;
	int				*philo_full;
	t_info			*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*eating_lock;
	pthread_mutex_t	*meal_counter_lock;
}					t_args;

typedef struct s_philo
{
	pthread_t		philosophers[200];
	t_args			args[200];
	int				phil_num[200];
	int				meal_counter[200];
	int				have_eaten[200];
	int				idx;
}					t_philo;

/* ************ PRINTING MESSAGES *************** */
void				ft_eating_msg(t_args *args);
void				ft_fork_taken(t_args *args, int time);
void				ft_death_msg(int time, t_args *args);
void				ft_sleeping_msg(t_args *args);
void				ft_thinking_msg(t_args *args);

/* ************ ARGUMENTS VALIDATION && SAVING *************** */
int				ft_valid_args(int argc, char **argv, t_info *info);
void				ft_save_info(t_info *info);

/* ************ INIT STRUCTS *************** */
void				ft_philo_init(t_philo *philo);
void				ft_init_forks(t_info *info);

/* ************ LOCKS INIT/DESTROY *************** */
void				ft_destroy_mutexes(t_info *info);
void				ft_init_forks(t_info *info);

/* ************ PHILOS AT WORK *************** */
void				ft_philos_atwork(t_philo *philo, t_info *info);
void				ft_think(t_args *args);
void				ft_sleep(t_args *args);
void				ft_eat(t_args *args);

void	ft_monitoring(t_philo *philo, t_info *info);

/* ************ PHILOS AT WORK HELPERS *************** */
long				ft_current_time(void);
void				ft_wait(long time);

#endif
