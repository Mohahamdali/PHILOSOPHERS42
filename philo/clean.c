/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:29:38 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/27 20:47:54 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	free(data);
}

void	ft_usleep(t_data *data, int time)
{
	long	start;

	start = current_time_ms();
	while (current_time_ms() - start < time)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->dead_lock);
			return ;
		}
		pthread_mutex_unlock(&data->dead_lock);
		usleep(200);
	}
	return ;
}
