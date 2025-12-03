/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/03 15:59:06 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_handler(const char *error_msg, int exit_code)
{
	printf("%s\n", error_msg);
	exit (exit_code);
}

void	*start_routine(void *arg)
{
	printf("Created new thread!\n");
	(void) arg;
	return (NULL);
}

void	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		error_handler("Usage: ./philo [num_of_philosophers] [time_to_die] "
			"[time_to_eat] [time_to_sleep] "
			"[opt: num_of_times_each_philosopher_must_eat]", EXIT_FAILURE);
	(void) argv;
}

int	main(int argc, char *argv[])
{
	t_philo	philo;
	validate_args(argc, argv);	
	if (pthread_create(&philo.philo, NULL, start_routine, NULL))
		printf("Error creating thread.\n");
	pthread_join(philo.philo, NULL);
	return (0);
}
