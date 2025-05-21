/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:37:07 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/20 17:28:33 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	*handle_single_philo(t_philo *philo)
{
	print_action(philo, "has taken a fork");
	print_action(philo, "died");
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

static void	eat_and_release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	print_action(philo, "is eating");
	philo->last_eat_ms = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data, philo->data->t_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	sleep_and_think(t_philo *philo, int thinktime)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->t_sleep);
	print_action(philo, "is thinking");
	usleep(thinktime * 1000);
}

void	*routine_philo(void *args)
{
	t_philo	*philo;
	int		thinktime;

	philo = (t_philo *)args;
	thinktime = (philo->data->t_die - philo->data->t_eat - philo->data->t_sleep) / 2;
	if (thinktime < 0)
		thinktime = 0;
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
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (NULL);
		}
		eat_and_release_forks(philo);
		if (philo->data->n_meals != -1 && philo->meals_eaten >= philo->data->n_meals)
			return (NULL);
		sleep_and_think(philo, thinktime);
	}
	return (NULL);
}
