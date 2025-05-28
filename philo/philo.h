/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:29:25 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/27 20:44:05 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philo;
	int				dead;
}	t_data;

typedef struct s_philo
{
	int				meals_eaten;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				id;
	t_data			*data;
	long			last_eat_ms;
}	t_philo;

int		ft_atoi(const char *str, int *check);
int		check_argc(t_data *data, char **av, int ac);
int		init_data(t_data *data);
void	init_philo(t_data *data);
void	*routine_philo(void *args);
int		create_thread_philo(t_data *data);
long	current_time_ms(void);
void	print_action(t_philo *philo, char *action);
void	cleanup(t_data *data);
void	ft_usleep(t_data *data, int time);
void	*monitor_thread(void *args);
void	eat_and_release_forks(t_philo *philo);
void	sleep_and_think(t_philo *philo);
void	put_forks(t_philo *philo);
int		join_thread(t_data *data, pthread_t *threads, pthread_t monitor);
int		init_philo_data(t_data *data, int i);
#endif