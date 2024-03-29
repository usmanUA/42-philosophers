
#include "../include/philo.h"

void    ft_eat(t_args *args)
{
    ft_eating_msg(args);
    *args->meal_counter += 1;
    ft_wait(args->info->eating_time);
}

void    ft_sleep(t_args *args)
{
    ft_sleeping_msg(args);
    ft_wait(args->info->sleeping_time);
}

void    ft_think(t_args *args)
{
    ft_thinking_msg(args);
}

void    ft_monitor_time(t_args *args, int wait)
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

int ft_stop_simulation(t_args *args, int wait, int unlock)
{
    ft_monitor_time(args, wait);
    if (*args->philo_died || (args->info->n_times_eat && *args->meal_counter >= args->info->n_times_eat))
    {
        if (unlock)
        {
            pthread_mutex_unlock(args->left_fork);
            pthread_mutex_unlock(args->right_fork);
        }
        return (1);
    }
    return (0);
}

