/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:34:36 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/26 15:29:19 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <wait.h>
# include <signal.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_meals;
	sem_t			*forks;
	t_philo			*philo;
	sem_t			*print;
	sem_t			*meals_lock;
	long			start_time;
}	t_data;

typedef struct s_philo
{
	int				meals_eaten;
	int				id;
	t_data			*data;
	long			last_eat_ms;
}	t_philo;

int		check_argc(t_data *data, char **av, int ac);
char	*ft_strdup(const char *src);
int		init_structs(t_data *data);
void	print_action_bonus(t_philo *philo, char *action);
long	current_time_ms(void);
void	routine_philo(t_philo *philo);
void	ft_usleep(t_data *data, int time);
void	clean_up(t_data *data, int flag, int *process);
void	*monitor_thread(void *args);

#endif