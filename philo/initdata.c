/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:29:33 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 18:28:23 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time_ms(void)
{
	struct timeval	ti;

	gettimeofday(&ti, NULL);
	return ((ti.tv_sec * 1000) + (ti.tv_usec / 1000));
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&data->meal_lock, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&data->dead_lock, NULL) == -1)
		return (-1);
	return (0);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (write(2, "can't allocate memory for forks\n", 33), -1);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (write(2, "can't allocate memory for philosophers\n", 40), -1);
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (-1);
		i++;
	}
	data->dead = 0;
	if (init_mutex(data) == -1)
		return (-1);
	if (create_thread_philo(data) == -1)
		return (-1);
	return (0);
}

int	create_thread_philo(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor;
	int			i;

	threads = malloc(sizeof(pthread_t) * data->num_philo);
	if (!threads)
		return (-1);
	i = 0;
	data->start_time = current_time_ms();
	while (i < data->num_philo)
	{
		init_philo_data(data, i);
		if (pthread_create(&threads[i], NULL, routine_philo,
				&data->philo[i]) != 0)
		{
			return (free(threads), -1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_thread, data) != 0)
		return (write(2, "Thread monitor creation error\n", 31), -1);
	if (join_thread(data, threads, monitor) == -1)
		return (free(threads), -1);
	free(threads);
	return (0);
}
