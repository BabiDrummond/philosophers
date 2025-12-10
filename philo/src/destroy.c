/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:29:15 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 21:52:12 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_table_mutexes(t_table *table, int m_count)
{
	if (m_count == 1)
		pthread_mutex_destroy(&table->death_lock);
	if (m_count == 2)
		pthread_mutex_destroy(&table->print_lock);
	if (m_count == 3)
		pthread_mutex_destroy(&table->meal_lock);
}

void	destroy_forks(t_table *table, int m_count)
{
	int	i;

	i = -1;
	while (++i < m_count)
		pthread_mutex_destroy(&table->philos[i].fork_r);
}

void	destroy_philos(t_table *table, int p_count)
{
	int	i;
	
	i = -1;
	while (++i < p_count)
		if (pthread_join(table->philos[i].thread_id, NULL))
			throw_error(JOIN_THREAD);
}

void	destroy_data(t_table *table, int mutex, int forks, int philos)
{
	destroy_table_mutexes(table, mutex);
	destroy_forks(table, forks);
	destroy_philos(table, philos);
	if (table && table->philos)
		free(table->philos);
}
