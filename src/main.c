/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 20:16:19 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_routine(void *arg)
{
	(void) arg;
	printf("Created new thread!\n");
	return (NULL);
}

void	init_table(t_table *table, int argc, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_of_eat = ft_atol(argv[5]);
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
		if (pthread_create(&table->philos[i].philo, NULL, start_routine, &table))
			printf("Error creating thread.\n");
	i = -1;
	while (++i < table->num_philos)
		if (pthread_join(table->philos[i].philo, NULL))
			printf("Error joining thread.\n");
}

int	main(int argc, char **argv)
{
	t_table	table;

	validate_input(argc, argv);
	init_table(&table, argc, argv);
	init_philos(&table);
	// init mutex?
	// start routine contem a logica do projeto (pegar garfos, comer, dormir)
	return (0);
}
