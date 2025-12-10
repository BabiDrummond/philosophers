/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:48:01 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 01:42:39 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_simulation_running(t_table *table)
{
	int	status;

	pthread_mutex_lock(&table->death_lock);
	status = table->is_running;
	pthread_mutex_unlock(&table->death_lock);
	return (status);
}

void	*start_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (is_simulation_running(philo->table))
	{
		taking_a_fork(philo);
		eating(philo); //eat (2 cases: 1 philo, more than one)
		sleeping(philo);
		thinking(philo); //think (0, algum calculo = resto do tempo até comer / 2, 100, 500)
	}
	return (NULL);
}
