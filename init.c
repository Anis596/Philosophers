/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 07:07:45 by abensaid          #+#    #+#             */
/*   Updated: 2026/01/10 08:23:54 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	valid_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (is_digit(av[i]) != 1)
		{
			printf("Arguments must be only numbers\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_data(t_data *data, char **av)
{
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nb_meals_max = ft_atol(av[5]);
	else
		data->nb_meals_max = -1;
}
