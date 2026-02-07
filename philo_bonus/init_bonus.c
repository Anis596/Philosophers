/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 07:07:45 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/07 08:52:08 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_digit(char *str)
{
	int		i;
	long	nb;

	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	if ((str[0] == '+' && ft_strlen(str) > 11) || (str[0] != '+'
			&& ft_strlen(str) > 10))
		return (1);
	nb = ft_atol(str);
	if (nb > __INT_MAX__)
		return (1);
	return (0);
}
int	valid_args(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	i = 1;
	while (i < ac)
	{
		if (is_digit(av[i]) != 0)
		{
			printf("Invalid Arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_args(t_data *data, char **av)
{
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nb_meals_max = ft_atol(av[5]);
	else
		data->nb_meals_max = -1;
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time_in_ms();
		data->philos[i].data = data;
		data->philos[i].pid = -1;
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_meals");
	data->forks = sem_open("/philo_forks", O_CREAT, 0644, data->nb_philo);
	data->write_sem = sem_open("/philo_write", O_CREAT, 0644, 1);
	data->meals_check = sem_open("/philo_meals", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->write_sem == SEM_FAILED
		|| data->meals_check == SEM_FAILED)
	{
		printf("Initialization failed\n");
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		printf("Initialization failed\n");
		return (1);
	}
	init_philos(data);
	return (0);
}
