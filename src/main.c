/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/05 18:27:28 by bmoreira         ###   ########.fr       */
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
	table->philos = malloc((table->num_philos + 1) * sizeof(t_philo));
	if (!table->philos)
		error_handler("Error to allocate philos.", EXIT_FAILURE);
}

void	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_mutex_init(&table->philos[i].fork_r, NULL))
			error_handler("Error initializing mutex.", EXIT_FAILURE);
		if (i >= 1)
			table->philos[i].fork_l = table->philos[i].fork_r;
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
		if (pthread_create(&table->philos[i].philo, NULL, start_routine, &table))
			error_handler("Error creating thread.", EXIT_FAILURE);
	i = -1;
	while (++i < table->num_philos)
		if (pthread_join(table->philos[i].philo, NULL))
			error_handler("Error joining thread.", EXIT_FAILURE);
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
