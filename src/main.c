/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:41:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 03:53:53 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*start_routine(void *arg)
{
	printf("Created new thread %d!\n", *(int *)arg);
	return (NULL);
}

void	init_table(t_table *table, int argc, char **argv)
{
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->num_of_eat = ft_atol(argv[5]);
}

void	init_philos(t_table *table, int philos_count)
{
	int	i;

	i = 0;
	while (i < philos_count)
	{
		table->philos[i].philo = pthread_create(&table->philos[i].philo, NULL, start_routine, &i);
		if (table->philos[i].philo)
			printf("Error creating thread.\n");
		pthread_join(table->philos[i].philo, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	validate_input(argc, argv);
	init_table(&table, argc, argv);
	init_philos(&table, ft_atol(argv[1]));
	// init philos
	// start routine contem a logica do projeto (pegar garfos, comer, dormir)
	// if (pthread_create(&philo.philo, NULL, start_routine, &philo))
	// 	printf("Error creating thread.\n");
	// pthread_join(philo.philo, NULL);
	return (0);
}
