/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 03:11:27 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_routine(void *arg)
{
	printf("Created new thread!\n");
	(void) arg;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	validate_input(argc, argv);
	// init
	// start routine contem a logica do projeto (pegar garfos, comer, dormir)
	if (pthread_create(&philo.philo, NULL, start_routine, &philo))
		printf("Error creating thread.\n");
	pthread_join(philo.philo, NULL);
	return (0);
}
