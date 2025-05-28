/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:50:09 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/27 21:38:20 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philosopher_dead(t_data *data, t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = current_time_ms();
	time_since_last_meal = current_time - philo->last_eat_ms;
	if (time_since_last_meal > data->t_die)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&data->dead_lock);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		pthread_mutex_unlock(&data->meal_lock);
		return (1);
	}
	return (0);
}

int	are_all_philosophers_full(t_data *data, int full_philosophers)
{
	if (data->n_meals == -1 || full_philosophers < data->num_philo)
		return (0);
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
	return (1);
}

int	monitor_philosophers(t_data *data)
{
	int		i;
	int		full_philosophers;
	t_philo	*current_philo;

	i = 0;
	full_philosophers = 0;
	while (i < data->num_philo)
	{
		current_philo = &data->philo[i];
		pthread_mutex_lock(&data->meal_lock);
		if (is_philosopher_dead(data, current_philo))
			return (1);
		if (data->n_meals != -1 && current_philo->meals_eaten >= data->n_meals)
			full_philosophers++;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (are_all_philosophers_full(data, full_philosophers));
}

void	*monitor_thread(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (!data->dead)
	{
		if (monitor_philosophers(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
