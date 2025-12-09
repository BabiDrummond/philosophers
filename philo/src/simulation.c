/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:48:01 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/08 22:36:46 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_now(void)
{
	struct timeval	now;
	
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	is_someone_dead(t_table *table)
{
	int	last_meal;
	int	meals_eaten;
	int	all_eaten;
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		last_meal = table->philos[i].last_meal;
		meals_eaten = table->philos[i].meals_eaten;
		pthread_mutex_unlock(&table->meal_lock);
		if (last_meal - table->start_time >= table->time_to_die)
		{
			pthread_mutex_lock(&table->death_lock);
			table->is_running = FALSE;
			pthread_mutex_unlock(&table->death_lock);
		}
		if (meals_eaten == table->max_meals)
			all_eaten++;
		if (all_eaten == table->num_philos)
		{
			pthread_mutex_lock(&table->death_lock);
			table->is_running = FALSE;
			pthread_mutex_unlock(&table->death_lock);
		}
	}
	return (table->is_running);
}

int is_simulation_running(t_table *table)
{
	int running;
	
	pthread_mutex_lock(&table->death_lock);
	running = is_someone_dead(table);
	pthread_mutex_unlock(&table->death_lock);
	return (running);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (is_simulation_running(philo->table))
	{
		//try_take_fork
		//eat (2 cases: 1 philo, more than one)
		//sleep
		//think
	}
	return (NULL);
}

void	start_monitor(t_table *table)
{
	//wait for all ready?
	while (is_simulation_running(table))
	{
		usleep(1000);
	}
}
