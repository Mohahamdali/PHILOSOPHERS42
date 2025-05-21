/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:56:33 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/21 18:46:20 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo_bonus.h"

void take_forks(t_philo *philo)
{
    sem_wait(philo->data->forks);
    print_action_bonus(philo, "has taken a fork");

    sem_wait(philo->data->forks);
    print_action_bonus(philo, "has taken a fork");
}

void eat_and_release(t_philo *philo)
{
    print_action_bonus(philo, "is eating");
    sem_wait(philo ->data -> meals_lock);
    philo ->last_eat_ms = current_time_ms();
    philo ->meals_eaten++;
    sem_post(philo->data ->meals_lock);
    ft_usleep(philo -> data, philo -> data -> t_eat);
    sem_post(philo->data->forks);
    sem_post(philo->data->forks);
}

void think_and_sleep(t_philo *philo, int thinktime)
{
    print_action_bonus(philo, "is sleeping");
    ft_usleep(philo -> data, philo -> data -> t_sleep);
    print_action_bonus(philo, "is thinking");
    usleep(thinktime * 1000);
}



void *monitor_thread(void *args)
{
    t_philo *philo = (t_philo *)args;
    t_data *data = philo ->data;
    long current_time;
    long max_time;
    usleep(200);
    while (1)
    {
        usleep(200);
        sem_wait(data ->meals_lock);
        current_time = current_time_ms();
        max_time = current_time -  philo->last_eat_ms;
        sem_post(data ->meals_lock);
        if (max_time > data -> t_die)
        {
            // sem_wait(data ->print);
            // printf ("%ld %d %s\n",current_time - data -> start_time, data->philo->id, "died");
            // sem_post(data ->print);
            print_action_bonus(philo,"died");
            // printf("Philosopher %d: Time since last meal: %ld, t_die: %d\n", philo->id, max_time, data->t_die);
            sem_post(data->kill);
            return NULL;
        }
        
    }
    return NULL;
}

void routine_philo(t_philo *philo)
{
    pthread_t monitor;

    int thinktime;
    thinktime = (philo->data->t_die - philo->data->t_eat - philo->data->t_sleep) / 2;
    if (pthread_create(&monitor, NULL, monitor_thread,philo) != 0)
        write(2,"error\n",7);
    pthread_detach(monitor);
    while (1)
    {
        take_forks(philo);  
   
        eat_and_release(philo);

        think_and_sleep(philo, thinktime);
    }
}

