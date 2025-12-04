/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:50:24 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 02:35:25 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	validate_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		error_handler("Usage: ./philo [num_of_philosophers] [time_to_die] "
			"[time_to_eat] [time_to_sleep] "
			"[opt: num_of_times_each_philosopher_must_eat]", EXIT_FAILURE);
	while (argv[i])
		if (ft_atol(argv[i++]) > INT_MAX)
			error_handler("Invalid argument provided.", EXIT_FAILURE);
}
