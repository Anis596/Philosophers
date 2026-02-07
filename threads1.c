/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 00:39:33 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/07 09:33:16 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_all_ate(t_data *data, t_philo *philo)
{
	int	i;
	int	finished;

	if (data->nb_meals_max == -1)
		return (0);
	finished = 0;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].meals_eaten >= data->nb_meals_max)
			finished++;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	if (finished == data->nb_philo)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
