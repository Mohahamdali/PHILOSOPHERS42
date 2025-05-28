/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:51:46 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 18:33:55 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	current_time_ms(void)
{
	struct timeval	ti;

	gettimeofday(&ti, NULL);
	return ((ti.tv_sec * 1000) + (ti.tv_usec / 1000));
}

void	print_action_bonus(t_philo *philo, char *action)
{
	sem_wait(philo->data->print);
	printf("%ld %d %s\n", current_time_ms() - philo->data->start_time,
		philo->id, action);
	sem_post(philo->data->print);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (write(2, "Error arguments\n", 16), 1);
	data = malloc(sizeof(t_data));
	if (check_argc(data, av, ac))
		clean_up(data, 1, NULL);
	init_structs(data);
	clean_up(data, 0, NULL);
}
