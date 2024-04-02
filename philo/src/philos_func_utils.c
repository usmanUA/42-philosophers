
#include "../include/philo.h"

void    ft_eat(t_args *args)
{
    *args->log->eaten = 1;
    *args->log->eaten_time = ft_current_time() - args->info->start_time;
    *args->time->meal_counter += 1;
    ft_wait(args->info->eating_time);
}

void    ft_sleep(t_args *args)
{
    *args->log->slept = 1;
    *args->log->slept_time = ft_current_time() - args->info->start_time;
    ft_wait(args->info->sleeping_time);
}

void    ft_think(t_args *args)
{
    *args->log->thought = 1;
    *args->log->thought_time = ft_current_time() - args->info->start_time;
}

void    ft_monitor_time(t_args *args, int wait)
{
    if (*args->time->start)
    {
        *args->time->start = 0;
        *args->time->start_counter = ft_current_time() - args->info->start_time;
        if (*args->time->start_counter < args->info->time_to_die)
            return ;
    }
    else
    {
        if (wait)
            ft_wait(args->info->last_meal);
        *args->time->time_counter = ft_current_time() - *args->time->current_time;
        if (*args->time->time_counter < args->info->time_to_die)
            return ;
    }
    if (!*args->philo_died)
    {
        *args->log->died_time = ft_current_time() - args->info->start_time;
        *args->log->died = 1;
    }
    args->info->philo_died = 1;
}

int ft_stop_simulation(t_args *args, int wait, int unlock)
{
    pthread_mutex_lock(args->stop_lock);
    ft_monitor_time(args, wait);
    if (*args->philo_died || (args->info->n_times_eat && *args->time->meal_counter >= args->info->n_times_eat))
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

