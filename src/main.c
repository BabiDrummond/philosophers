/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 03:45:19 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_routine(void *arg)
{
	printf("Created new thread!\n");
	(void) arg;
	return (NULL);
}

void	init_table(t_table *table, int argc, char **argv)
{
	table->time_to_die = argv[2];
	table->time_to_eat = argv[3];
	table->time_to_sleep = argv[4];
	if (argc == 6)
		table->num_of_eat = argv[5];
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	philo;

	validate_input(argc, argv);
	init_table(&table, argc, argv);
	// init philos
	// start routine contem a logica do projeto (pegar garfos, comer, dormir)
	if (pthread_create(&philo.philo, NULL, start_routine, &philo))
		printf("Error creating thread.\n");
	pthread_join(philo.philo, NULL);
	return (0);
}
