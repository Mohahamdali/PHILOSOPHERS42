/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:29:33 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/17 19:31:35 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long current_time_ms()
{
    struct timeval ti;
    gettimeofday(&ti,NULL);

    return ((ti.tv_sec * 1000) + (ti.tv_usec / 1000));
}


int init_data (t_data *data)
{
    int i = 0;
    data ->forks = malloc (sizeof(pthread_mutex_t) * data ->num_philo);
    if (!data -> forks)
        return (write(2, "can't allocate memory for forks\n", 33),-1);
    data ->philo = malloc (sizeof(t_philo) * data ->num_philo);
    if (!data -> philo)
        return ( write(2, "can't allocate memory for philosophers\n", 40),-1);
    while (i < data ->num_philo)
    {
        pthread_mutex_init(&data ->forks[i], NULL);
        i++;
    }
    data -> dead = 0;
    pthread_mutex_init (&data ->print,NULL);
    pthread_mutex_init(&data ->meal_lock,NULL);
    pthread_mutex_init (&data -> dead_lock, NULL);
    create_thread_philo(data);
    return 0;
}


void join_thread(t_data *data, pthread_t *threads, pthread_t monitor)
{
    int i = 0;
    while (i < data ->num_philo)
    {
        pthread_join(threads[i],NULL);
        i++;
    }
    pthread_join (monitor, NULL);
}


void  create_thread_philo (t_data *data)
{
    pthread_t *threads = malloc (sizeof(pthread_t) * data ->num_philo);
    pthread_t monitor;
    int i;

    i = 0;
    data->start_time = current_time_ms();
    while (i < data -> num_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].meals_eaten = 0;
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % data->num_philo];
        data->philo[i].data = data;
        data->philo[i].last_eat_ms =  data->start_time;
        if (pthread_create(&threads[i], NULL, routine_philo, &data-> philo[i]) != 0)
        {
            write(2, "Thread creation error\n", 23);
        }
        i++;
    }
    if (pthread_create(&monitor, NULL, monitor_thread,data) != 0)
        write(2, "Thread monitor creation error\n", 31);
   join_thread(data,threads,monitor);
   free(threads);
}
