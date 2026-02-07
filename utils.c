/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 07:02:53 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/07 08:46:27 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	sign;
	long	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_lock);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	time = (get_time_in_ms() - philo->data->start_time);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

int	dead_loop(t_philo *philo)
{
	int	flag;

	pthread_mutex_lock(&philo->data->dead_lock);
	flag = philo->data->dead_flag;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (flag);
}

void	clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
