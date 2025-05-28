/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:37:07 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/27 21:36:17 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*handle_single_philo(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->data->num_philo == 1)
		return (handle_single_philo(philo));
	while (1)
	{
		if (check_death(philo))
			return (NULL);
		take_forks(philo);
		if (check_death(philo))
		{
			put_forks(philo);
			return (NULL);
		}
		eat_and_release_forks(philo);
		if (philo->data->n_meals != -1
			&& philo->meals_eaten >= philo->data->n_meals)
			return (NULL);
		sleep_and_think(philo);
	}
	return (NULL);
}
