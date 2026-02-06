/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:30:42 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/06 08:57:09 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define _XOPEN_SOURCE 700
# define _GNU_SOURCE
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_philo;
	int				nb_meals_max;// L'argument optionnel
	long			start_time;
	sem_t			*forks;
	sem_t			*write_sem;
	sem_t			*meals_check;
	t_philo			*philos;// Tableau des philosophes
};

struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	t_data			*data;	// Lien vers les règles globales
	pid_t			pid;
};

long	ft_atol(const char *str);
long	get_time_in_ms(void);
int		valid_args(int ac, char **av);
int		parse_args(t_data *data, char **av);
int		init_data(t_data *data);
void	*monitor_death(void *arg);
void	*routine(void *arg);
void	kill_all(t_data *data);
void	exit_handler(t_data *data);
int		start_simulation(t_data *data);
void	print_action(char *str, t_philo *philo);
void	clean(t_data *data);

#endif