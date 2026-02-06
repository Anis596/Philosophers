/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 07:02:53 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/06 08:04:06 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_wait(philo->data->write_sem);
	time = (get_time_in_ms() - philo->data->start_time);
	printf("%ld %d %s\n", time, philo->id, str);
	sem_post(philo->data->write_sem);
}

void	clean(t_data *data)
{
	sem_close(data->forks);
	sem_unlink("/philo_forks");
	sem_close(data->write_sem);
	sem_close(data->meals_check);
	sem_unlink("/philo_write");
	sem_unlink("/philo_meals");
	if (data->philos)
		free(data->philos);
}
