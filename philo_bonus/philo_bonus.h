/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:30:42 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/06 06:11:51 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>

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
	int				dead_flag;// 1 si quelqu'un est mort, 0 sinon
	sem_t			*forks;
	sem_t			*write_sem;
	sem_t			*meals_check;
	t_philo			*philos;// Tableau des philosophes
};

struct s_philo
{
	pthread_t		thread_id;
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
void	think_and_sleep(t_philo *philo);
void	*routine(void *arg);
int		start_simulation(t_data *data);
void	print_action(char *str, t_philo *philo);
int		check_if_all_ate(t_data *data, t_philo *philo);
void	monitor(t_data *data, t_philo *philo);
void	clean(t_data *data);

#endif