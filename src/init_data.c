/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:10:29 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/07 14:48:19 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	i = -1;
	table->num_philos = safe_atoi(argv[1]);
	table->time_to_die = safe_atoi(argv[2]);
	table->time_to_eat = safe_atoi(argv[3]);
	table->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		table->num_of_eat = safe_atoi(argv[5]);
	else
		table->num_of_eat = 0;
	table->philos = malloc((table->num_philos + 1) * sizeof(t_philo));
	if (!table->philos)
		return (throw_error(NULL, 0, "Error allocating philos."));
	return (SUCCESS);
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		memset(&table->philos[i].fork_r, 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&table->philos[i].fork_r, NULL))
			return (throw_error(table, i, "Error initializing mutex."));
		if (i >= 1)
			table->philos[i].fork_l = table->philos[i - 1].fork_r;
	}
	return (SUCCESS);
}

static int	init_philos(t_table *table)
{
	struct timeval	start;
	int				i;

	i = -1;
	gettimeofday(&start, NULL);
	table->start_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	while (++i < table->num_philos)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		if (pthread_create(&table->philos[i].thread_id, NULL, start_routine,
				&table->philos[i]))
			return (throw_error(table, table->num_philos,
				"Error creating thread."));
	}
	i = -1;
	while (++i < table->num_philos)
		if (pthread_join(table->philos[i].thread_id, NULL))
			return (throw_error(table, table->num_philos,
				"Error joining thread."));
	return (SUCCESS);
}

int	init_data(t_table *table, int argc, char **argv)
{
	if (!init_table(table, argc, argv)
		|| !init_mutex(table)
		|| !init_philos(table))
		return (FAILURE);
	return (SUCCESS);
}
