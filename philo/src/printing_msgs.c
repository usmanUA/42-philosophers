
#include "../include/philo.h"

void    ft_fork_msg(t_args *args)
{
    pthread_mutex_lock(args->print_lock);
    printf("%d %d has taken a fork.\n", *args->log->left_fork_taken_time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_eating_msg(t_args *args)
{
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is eating.\n", *args->log->eaten_time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_sleeping_msg(t_args *args)
{
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is sleeping.\n", *args->log->slept_time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

void    ft_thinking_msg(t_args *args)
{
    pthread_mutex_lock(args->print_lock);
    printf("%d %d is thinking.\n", *args->log->thought_time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}


void    ft_death_msg(t_args *args)
{
    pthread_mutex_lock(args->print_lock);
    printf("%d %d died.\n", *args->log->died_time, *(args->phil_num));
    pthread_mutex_unlock(args->print_lock);
}

