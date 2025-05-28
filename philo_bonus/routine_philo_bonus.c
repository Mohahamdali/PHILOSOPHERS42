/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:56:33 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/27 13:31:22 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(2000);
	sem_wait(philo->data->forks);
	print_action_bonus(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action_bonus(philo, "has taken a fork");
}

void	eat_and_release(t_philo *philo)
{
	print_action_bonus(philo, "is eating");
	sem_wait(philo->data->meals_lock);
	philo->last_eat_ms = current_time_ms();
	philo->meals_eaten++;
	sem_post(philo->data->meals_lock);
	ft_usleep(philo->data, philo->data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	think_and_sleep(t_philo *philo)
{
	print_action_bonus(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->t_sleep);
	print_action_bonus(philo, "is thinking");
}

void	routine_philo(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_thread, philo) != 0)
	{
		write(2, "error\n", 7);
		return ;
	}
	while (1)
	{
		take_forks(philo);
		eat_and_release(philo);
		think_and_sleep(philo);
	}
}
