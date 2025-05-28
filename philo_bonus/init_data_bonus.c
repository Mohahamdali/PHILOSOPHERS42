/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:31 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 18:33:40 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(t_data *data, int time)
{
	long	start;

	(void)data;
	start = current_time_ms();
	while (current_time_ms() - start < time)
	{
		usleep(200);
	}
	return ;
}

void	main_monitor(t_data *data, int *sub_process)
{
	int	i;
	int	status;
	int	j;

	i = 0;
	status = 0;
	j = 0;
	while (i < data->num_philo)
	{
		if (waitpid(-1, &status, 0) == -1)
			clean_up(data, 1, sub_process);
		if (status != 0)
		{
			while (j < data->num_philo)
			{
				if (kill(sub_process[j], SIGKILL) == -1)
					clean_up(data, 1, sub_process);
				j++;
			}
			break ;
		}
		i++;
	}
}

void	check_process(t_data *data, int *sub_process, int i)
{
	if (sub_process[i] == -1)
	{
		clean_up(data, 1, sub_process);
	}
}

void	init_philos(t_data *data)
{
	int		i;
	pid_t	*sub_process;

	i = 0;
	sub_process = malloc (sizeof(pid_t) * data -> num_philo);
	data->start_time = current_time_ms();
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].last_eat_ms = data->start_time;
		sub_process[i] = fork();
		if (sub_process[i] == 0)
		{
			routine_philo(&data->philo[i]);
			exit(0);
		}
		check_process(data, sub_process, i);
		i++;
	}
	main_monitor(data, sub_process);
	free(sub_process);
}

int	init_structs(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!(data->philo))
		clean_up(data, 1, NULL);
	sem_unlink("/forks");
	sem_unlink("/print_0");
	sem_unlink("/meals_lock");
	data->forks = sem_open("/forks", O_CREAT, 0666, data->num_philo);
	data->print = sem_open("/print_0", O_CREAT, 0666, 1);
	data->meals_lock = sem_open("/meals_lock", O_CREAT, 0666, 1);
	init_philos(data);
	return (0);
}
