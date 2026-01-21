/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:49:52 by abensaid          #+#    #+#             */
/*   Updated: 2026/01/21 01:01:07 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//typedef struct s_bite
//{
//	int				*pt_compteur;
//	pthread_mutex_t	*mutex1;
//}					t_bite;

//void	*routine(void *arg)
//{
//	int		i;
//	t_bite	*bite;

//	bite = (t_bite *)arg;
//	i = 0;
//	while (i < 1000000)
//	{
//		pthread_mutex_lock(bite->mutex1);
//		(*bite->pt_compteur)++;
//		pthread_mutex_unlock(bite->mutex1);
//		i++;
//	}
//	return (NULL);
//}

//int	main(void)
//{
//	pthread_t		thread0;
//	pthread_t		thread1;
//	int				compteur;
//	pthread_mutex_t	mutex;
//	t_bite			bytes;

//	long start_time; // Pour stocker le début
//	long end_time;   // Pour stocker la fin
//	compteur = 0;
//	bytes.pt_compteur = &compteur;
//	bytes.mutex1 = &mutex;
//	pthread_mutex_init(&mutex, NULL);
//	start_time = get_time_in_ms();
//	printf("Début du calcul à : %ld ms\n", start_time);
//	pthread_create(&thread0, NULL, &routine, &bytes);
//	pthread_create(&thread1, NULL, &routine, &bytes);
//	pthread_join(thread0, NULL);
//	pthread_join(thread1, NULL);
//	end_time = get_time_in_ms();
//	printf("Result = %d\n", compteur);
//	// 3. On affiche la durée totale
//	printf("Durée totale de l'opération : %ld ms\n", end_time - start_time);
//	pthread_mutex_destroy(&mutex);
//	return (0);
//}

int	main(int ac, char **av)
{
	t_data	data;

	if (valid_args(ac, av) == 1)
	{
		return (1);
	}
	if (parse_args(&data, av) == 1)
	{
		printf("Invalid arguments values\n");
		return (1);
	}
	if (init_data(&data) == 1)
	{
		printf("Initialization failed\n");
		return (1);
	}
	start_simulation(&data);
	clean(&data);
	return (0);
}
