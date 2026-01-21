/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:30:42 by abensaid          #+#    #+#             */
/*   Updated: 2026/01/21 01:00:33 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

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
	pthread_mutex_t	dead_lock;// Protège dead_flag
	pthread_mutex_t	write_lock;// Protège les printf
	pthread_mutex_t	*forks;// Tableau réel des mutex (fourchettes)
	t_philo			*philos;// Tableau des philosophes
};

struct s_philo
{
	pthread_t		thread_id;
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	t_data			*data;	// Lien vers les règles globales
	pthread_mutex_t	*left_fork;// Pointeur vers la fourchette gauche
	pthread_mutex_t	*right_fork;// Pointeur vers la fourchette droite
	pthread_mutex_t	meal_lock;// Protège last_meal_time
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
int		dead_loop(t_philo *philo);
int		check_if_all_ate(t_data *data, t_philo *philo);
void	monitor(t_data *data, t_philo *philo);
void	clean(t_data *data);

#endif