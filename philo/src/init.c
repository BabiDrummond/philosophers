/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:10:29 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 00:33:15 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_table(t_table *table, int argc, char **argv)
{
	table->num_philos = safe_atoi(argv[1]);
	table->time_to_die = safe_atoi(argv[2]);
	table->time_to_eat = safe_atoi(argv[3]);
	table->time_to_sleep = safe_atoi(argv[4]);
	table->is_running = TRUE;
	memset(table->locks, 0, MAX);
	if (argc == 6)
		table->max_meals = safe_atoi(argv[5]);
	else
		table->max_meals = 0;
	table->philos = malloc((table->num_philos + 1) * sizeof(t_philo));
	if (!table->philos)
		return (throw_error(NULL, 0, 0, ALLOC));
	return (TRUE);
}

static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->death_lock, NULL))
		return (throw_error(table, 0, 0, MUTEX));
	table->locks[DEATH] = TRUE;
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (throw_error(table, 0, 0, MUTEX));
	table->locks[PRINT] = TRUE;
	if (pthread_mutex_init(&table->meal_lock, NULL))
		return (throw_error(table, 0, 0, MUTEX));
	table->locks[MEAL] = TRUE;
	return (TRUE);
}

static int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		memset(&table->philos[i].fork_r, 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&table->philos[i].fork_r, NULL))
			return (throw_error(table, i, 0, FORKS));
		if (i >= 1)
			table->philos[i].fork_l = table->philos[i - 1].fork_r;
	}
	return (TRUE);
}

static int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time_now();
	while (++i < table->num_philos)
	{
		table->philos[i].philo_id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].table = table;
		if (pthread_create(&table->philos[i].thread_id, NULL, start_simulation,
			&table->philos[i]))
				return (throw_error(table, table->num_philos, i, THREADS));
	}
	return (TRUE);
}

int	init_data(t_table *table, int argc, char **argv)
{
	if (!init_table(table, argc, argv)
		|| !init_mutexes(table)
		|| !init_forks(table)
		|| !init_philos(table))
		return (FALSE);
	return (TRUE);
}
