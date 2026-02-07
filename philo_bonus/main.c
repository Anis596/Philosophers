/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:49:52 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/07 08:30:44 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_exit(t_data *data)
{
	clean(data);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_meals");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (valid_args(ac, av) == 1 || parse_args(&data, av) == 1)
		return (1);
	if (init_data(&data) == 1)
		return (1);
	start_simulation(&data);
	clean_exit(&data);
	return (0);
}
