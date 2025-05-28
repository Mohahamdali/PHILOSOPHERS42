/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:36:46 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 17:39:14 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat_and_release_forks(t_philo *philo)
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

void	sleep_and_think(t_philo *philo)
{
	int	thinktime;

	thinktime = (philo->data->t_die - philo->data->t_eat
			- philo->data->t_sleep) / 2;
	print_action(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->t_sleep);
	print_action(philo, "is thinking");
	if (philo->data->t_die <= 1200 && thinktime > 0)
		usleep(thinktime * 1000);
}
