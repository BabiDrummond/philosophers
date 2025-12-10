/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:29:15 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 01:11:28 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_philos(t_table *table, int p_count)
{
	int	i;

	i = -1;
	while (++i < p_count)
		if (pthread_join(table->philos[i].thread_id, NULL))
			printf("Error joining thread.\n");
}

static void	destroy_forks(t_table *table, int f_count)
{
	int	i;

	i = -1;
	while (++i < f_count)
		pthread_mutex_destroy(&table->philos[i].fork_r);
}

static void	destroy_mutexes(t_table *table)
{
	if (table->locks[DEATH])
		pthread_mutex_destroy(&table->death_lock);
	if (table->locks[PRINT])
		pthread_mutex_destroy(&table->print_lock);
	if (table->locks[MEAL])
		pthread_mutex_destroy(&table->meal_lock);
}

void	destroy_data(t_table *table, int forks, int philos)
{
	if (philos)
		destroy_philos(table, philos);
	if (forks)
		destroy_forks(table, forks);
	if (table && table->locks[DEATH])
		destroy_mutexes(table);
	if (table && table->philos)
		free(table->philos);
}
