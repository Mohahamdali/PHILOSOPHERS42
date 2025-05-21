/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:29:11 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/16 16:01:49 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->dead_lock);
		return ;
	}
	current_time = current_time_ms();
	printf("%ld %d %s\n", current_time - philo->data->start_time,
		philo->id, action);
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->data->print);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error arguments\n", 16);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (check_argc(data, av, ac))
	{
		cleanup(data);
		return (1);
	}
	if (init_data(data) == -1)
	{
		cleanup(data);
		return (1);
	}
	cleanup(data);
	return (0);
}
