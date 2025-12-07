/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:50:24 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/07 15:59:13 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	validate_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (throw_error(NULL, 0, "Usage: ./philo [num_of_philosophers] "
			"[time_to_die] [time_to_eat] [time_to_sleep] "
			"[opt: num_of_times_each_philosopher_must_eat]"));
	while (argv[++i])
		if ((safe_atoi(argv[i]) <= 0 || safe_atoi(argv[i]) > INT_MAX))
			return (throw_error(NULL, 0, "Invalid argument provided"));
	return (SUCCESS);
}
