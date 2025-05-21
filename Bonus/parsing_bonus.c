/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhamdali <mhamdali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:51:42 by mhamdali          #+#    #+#             */
/*   Updated: 2025/05/16 08:51:58 by mhamdali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_valid_numbre(char *str)
{
	if (*str == '\0')
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
		{
			write(2, "Error\n", 6);
			return (1);
		}
		str++;
	}
	return (0);
}

static int	check_overflow(long n)
{
	if (n == 0 || n < INT_MIN || n > INT_MAX)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str, int *check)
{
	unsigned long	result;
	size_t			i;
	int				sign;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	*check = check_overflow(result * sign);
	return ((int)result * sign);
}

int	check_argc(t_data *data, char **av, int ac)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (av[i])
	{
		check = check_valid_numbre(av[i]);
		if (check)
			return (1);
		ft_atoi(av[i], &check);
		if (check)
			return (1);
		i++;
	}
	data->num_philo = ft_atoi(av[1], &check);
	data->t_die = ft_atoi(av[2], &check);
	data->t_eat = ft_atoi(av[3], &check);
	data->t_sleep = ft_atoi(av[4], &check);
	if (ac == 6)
		data->n_meals = ft_atoi(av[5], &check);
	else if (ac == 5)
		data->n_meals = -1;
	return (0);
}
