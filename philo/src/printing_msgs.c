
#include "../include/philo.h"

void    ft_fork_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d has taken a fork.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_eating_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is eating.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_sleeping_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is sleeping.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_thinking_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is thinking.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}


void    ft_death_msg(t_args *args)
{
    int time;

    time = (int)ft_current_time() - args->info->start_time;
    pthread_mutex_lock(args->print_lock);
    printf("%d %d died.\n", time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

