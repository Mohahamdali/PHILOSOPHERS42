/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_two_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:57:33 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 18:34:10 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	post_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
	exit(0);
}

void	*monitor_thread(void *args)
{
	t_philo	*philo;
	t_data	*data;
	long	current_time;
	long	max_time;

	philo = (t_philo *)args;
	data = philo->data;
	while (1)
	{
		usleep(100);
		sem_wait(data->meals_lock);
		current_time = current_time_ms();
		max_time = current_time - philo->last_eat_ms;
		sem_post(data->meals_lock);
		if (max_time > data->t_die)
		{
			sem_wait(data->print);
			printf("%ld %d %s\n", current_time - data->start_time,
				philo->id, "died");
			exit(1);
		}
		else if (data->n_meals != -1 && philo->meals_eaten >= data->n_meals)
			post_forks(data);
	}
	return (NULL);
}
