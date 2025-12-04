/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:50:24 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 03:35:28 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	validate_quantity(int argc)
{
	if (argc != 5 && argc != 6)
		error_handler("Usage: ./philo [num_of_philosophers] [time_to_die] "
			"[time_to_eat] [time_to_sleep] "
			"[opt: num_of_times_each_philosopher_must_eat]", EXIT_FAILURE);
}

void	validate_arguments(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX)
			error_handler("Invalid argument provided.", EXIT_FAILURE);	
}

void	validate_input(int argc, char **argv)
{
	validate_quantity(argc);
	validate_arguments(argv);
}
