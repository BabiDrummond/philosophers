/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:47:37 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/11 05:43:36 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_someone_dead(t_philo *philo, int next_meal, long time)
{
	if (next_meal >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->is_running = FALSE;
		pthread_mutex_unlock(&philo->table->death_lock);
		pthread_mutex_lock(&philo->table->print_lock);
		printf("\033[90m%ld %d has died 💀\033[0m\n",
			time - philo->table->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->table->print_lock);
		return (TRUE);
	}
	return (FALSE);
}

static int	is_all_eaten(t_table *table, int all_eaten)
{
	if (table->max_meals > 0)
	{
		if (all_eaten == table->num_philos)
		{
			pthread_mutex_lock(&table->death_lock);
			table->is_running = FALSE;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_lock(&table->print_lock);
			printf("All philosophers have eaten %d times 🥣\n", table->max_meals);
			pthread_mutex_unlock(&table->print_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	start_monitor(t_table *table)
{
	int		i;
	int		all_eaten;
	long	now;
	long	next_meal;

	while (is_simulation_running(table))
	{
		i = -1;
		all_eaten = 0;
		while (++i < table->num_philos)
		{
			pthread_mutex_lock(&table->meal_lock);
			now = get_time_now();
			next_meal = now - table->philos[i].last_meal;
			if (table->philos[i].meals_eaten == table->max_meals)
				all_eaten++;
			pthread_mutex_unlock(&table->meal_lock);
			if (is_someone_dead(&table->philos[i], next_meal, now)
				|| is_all_eaten(table, all_eaten))
				break ;
		}
		usleep(100);
	}
}
