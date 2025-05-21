/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:13:31 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/21 16:04:11 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"




void ft_usleep (t_data *data, int time)
{
    (void)data;
    long start = current_time_ms();
    while (current_time_ms() - start < time)
    {
        usleep(200);
    }
    return ;
}


void init_philos (t_data *data)
{
    int i = 0;
    data -> start_time = current_time_ms();
    pid_t sub_process[data -> num_philo];
    
    while (i < data->num_philo)
    {
        data ->philo[i].id = i + 1;
        data ->philo[i].meals_eaten = 0;
        data ->philo[i].data = data;
        data ->philo[i].last_eat_ms = data -> start_time;
        sub_process[i] = fork();
        if (sub_process[i] == 0)
        {
            routine_philo(&data -> philo[i]);
            exit(0);
        }
        if (sub_process[i] == -1)
        {
           write(2,"creation process its failed\n",29);
           exit(1);
        }
        i++;
    }
    i = 0;
    sem_wait(data->kill); 
    while (i < data -> num_philo)
    {
        kill(sub_process[i],SIGKILL);
        i++;
    }
    i = 0;
    while (i < data -> num_philo)
    {
        waitpid(sub_process[i],NULL,0);
        i++;
    }
}


int init_structs (t_data *data)
{
    if (!(data ->philo = malloc (sizeof(t_philo) * data -> num_philo)))
       exit(1);
    sem_unlink("/forks");
    sem_unlink("/print_0");
    sem_unlink("/meals_lock");
    sem_unlink("/kill_lock");
    data -> forks = sem_open("/forks", O_CREAT, 0666, data ->num_philo);
    data -> print = sem_open("/print_0", O_CREAT, 0666,1);
    data -> meals_lock = sem_open("/meals_lock", O_CREAT, 0666,1);
    data -> kill = sem_open("/kill_lock", O_CREAT, 0666,0);
    init_philos(data);
    return (0);
}
