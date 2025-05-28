/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initdata_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:57 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 18:21:37 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_thread(t_data *data, pthread_t *threads, pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (-1);
	return (0);
}

int	init_philo_data(t_data *data, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].meals_eaten = 0;
	data->philo[i].left_fork = &data->forks[i];
	data->philo[i].right_fork = &data->forks[(i + 1) % data->num_philo];
	data->philo[i].data = data;
	data->philo[i].last_eat_ms = data->start_time;
	return (0);
}
