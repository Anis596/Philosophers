/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 06:05:19 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/06 09:03:16 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->meals_check);
		time = get_time_in_ms() - philo->last_meal_time;
		if (time >= philo->data->time_to_die)
		{
			sem_wait(philo->data->write_sem);
			printf("%ld %d died\n", get_time_in_ms() - philo->data->start_time,
				philo->id);
			sem_post(philo->data->meals_check);
			exit(1);
		}
		sem_post(philo->data->meals_check);
		usleep(1000);
	}
}

void	eat_think_and_sleep(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action("has taken a fork", philo);
	sem_wait(philo->data->forks);
	print_action("has taken a fork", philo);
	sem_wait(philo->data->meals_check);
	print_action("is eating", philo);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	sem_post(philo->data->meals_check);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	print_action("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
	print_action("is thinking", philo);
}

void	*routine(void *arg)
{
	pthread_t	death;
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_create(&death, NULL, &monitor_death, philo);
	pthread_detach(death);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->data->nb_philo == 1)
		{
			sem_wait(philo->data->forks);
			usleep(philo->data->time_to_die * 1000);
			sem_post(philo->data->forks);
			return (NULL);
		}
		eat_think_and_sleep(philo);
	}
	return (NULL);
}

void	exit_handler(t_data *data, t_philo *philo)
{
	int	status;
	int	finished;

	finished = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_all(data);
				return ;
			}
			else if (WEXITSTATUS(status) == 0)
				finished++;
		}
		if (finished == data->nb_philo)
			return ;
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			routine(&data->philos[i]);
			exit(0);
		}
		if (data->philos[i].pid < 0)
			exit(1);
		i++;
	}
}
