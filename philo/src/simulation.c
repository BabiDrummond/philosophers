/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:48:01 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/11 03:38:16 by bmoreira         ###   ########.fr       */
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

void *simulation_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_r);
	safe_print(philo, "\033[93m%ld %d has taken a fork 🍴\033[0m\n");
	wait_action(philo, philo->table->time_to_die);
	pthread_mutex_unlock(&philo->fork_r);
	return (NULL);
}

void	*start_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->table->num_philos == 1)
		return (simulation_one_philo(philo));
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (is_simulation_running(philo->table))
	{
		taking_a_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo); //think (0, algum calculo = resto do tempo até comer / 2, 100, 500)
	}
	return (NULL);
}
