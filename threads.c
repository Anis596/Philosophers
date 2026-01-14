/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 06:05:19 by abensaid          #+#    #+#             */
/*   Updated: 2026/01/14 04:52:17 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!dead_loop(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken a fork", philo);
		print_action("is eating", philo);
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal_time = get_time_in_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_lock);
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action("is sleeping", philo);
		usleep(philo->data->time_to_sleep * 1000);
		print_action("is thinking", philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	return (0);
}

static int	philo_died(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->meal_lock);
	time = get_time_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time >= philo->data->time_to_die)
		return (1);
	return (0);
}

void	monitor(t_data *data, t_philo *philo)
{
	int		i;
	long	last_meal;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (philo_died(&philo[i]))
			{
				print_action("died", &philo[i]);
				pthread_mutex_lock(&data->dead_lock);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->dead_lock);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
