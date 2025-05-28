/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:11:58 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 18:32:27 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_forks_print(t_data *data)
{
	if (data->forks)
	{
		sem_close(data->forks);
		sem_unlink("/forks");
		data->forks = NULL;
	}
	if (data->print)
	{
		sem_close(data->print);
		sem_unlink("/print_0");
		data->print = NULL;
	}
	if (data->meals_lock)
	{
		sem_close(data->meals_lock);
		sem_unlink("/meals_lock");
		data->meals_lock = NULL;
	}
}

void	clean_up(t_data *data, int flag, int *process)
{
	if (process)
	{
		free(process);
		process = NULL;
	}
	if (data->philo)
	{
		free(data->philo);
		data->philo = NULL;
	}
	clean_forks_print(data);
	free(data);
	data = NULL;
	exit(flag);
}
