/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:48:01 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/07 16:01:16 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_passed(t_philo *philo)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000)
		- philo->table->start_time);
}

int	is_philo_alive(t_philo *philo)
{
	int	is_alive;

	is_alive = 0;
	pthread_mutex_lock(&philo->fork_r);
	pthread_mutex_lock(&philo->fork_l);
	if (get_time_passed(philo) < philo->table->time_to_die)
		is_alive = 1;
	pthread_mutex_unlock(&philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	return (is_alive);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("Time passed: %lu\n", get_time_passed(philo));
	printf("%lu: Created new thread! Philo_id: %d, Thread_id: %lu\n",
		philo->table->start_time, philo->philo_id, philo->thread_id);
	while (is_philo_alive(philo))
		printf("%lu is alive\n", get_time_passed(philo));
	printf("%lu is dead\n", get_time_passed(philo));
	return (NULL);
}

void	*start_monitor(void *arg)
{
	t_table	*table;

	table = (t_table *) arg;
	return (NULL);
}
