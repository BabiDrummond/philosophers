/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:48:01 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/07 23:14:57 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_passed(long start)
{
	return (get_time_now() - start);
}

long	get_time_now(void)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	is_philo_alive(t_philo *philo)
{
	if (get_time_passed(philo->last_meal) < philo->table->time_to_die)
		return (TRUE);
	pthread_mutex_lock(&philo->table->monitor);
	philo->table->is_running = FALSE;
	pthread_mutex_unlock(&philo->table->monitor);
	return (FALSE);
}

int is_someone_dead(t_table *table)
{
	int	running;
	
	running = TRUE;
	pthread_mutex_lock(&table->monitor);
	if (!table->is_running)
		running = FALSE;
	pthread_mutex_unlock(&table->monitor);
	return (running);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	printf("Start");
	while (!is_someone_dead(philo->table) && !is_philo_alive(philo))
		printf("%lu %d is eating", get_time_now(), philo->philo_id);
	return (NULL);
}