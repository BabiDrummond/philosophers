/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:47:37 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/13 23:12:25 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_someone_dead(t_table *table)
{
	int		i;
	long	now;
	long	next_meal;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		now = get_time_now();
		next_meal = now - table->philos[i].last_meal;
		pthread_mutex_unlock(&table->meal_lock);
		if (next_meal >= table->time_to_die)
		{
			pthread_mutex_lock(&table->death_lock);
			table->is_running = FALSE;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_lock(&table->print_lock);
			printf("\033[90m%ld %d has died 💀\033[0m\n",
				now - table->start_time, table->philos[i].philo_id);
			pthread_mutex_unlock(&table->print_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	is_all_eaten(t_table *table)
{
	int	i;
	int	all_eaten;

	i = -1;
	all_eaten = 0;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (table->philos[i].meals_eaten == table->max_meals)
			all_eaten++;
		pthread_mutex_unlock(&table->meal_lock);
		if (all_eaten == table->num_philos)
		{
			pthread_mutex_lock(&table->death_lock);
			table->is_running = FALSE;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_lock(&table->print_lock);
			printf("All philosophers have eaten %d times 🥣\n",
				table->max_meals);
			pthread_mutex_unlock(&table->print_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	start_monitor(t_table *table)
{
	while (is_simulation_running(table))
	{
		if (is_someone_dead(table))
			break ;
		if (table->max_meals > 0 && is_all_eaten(table))
			break ;
		usleep(50);
	}
}
