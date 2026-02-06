/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abensaid <abensaid@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 02:49:52 by abensaid          #+#    #+#             */
/*   Updated: 2026/02/06 07:40:30 by abensaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (valid_args(ac, av) == 1 || parse_args(&data, av) == 1)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	if (init_data(&data) == 1)
		return (1);
	start_simulation(&data);
	clean(&data);
	return (0);
}
