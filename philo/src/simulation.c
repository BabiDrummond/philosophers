/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:48:01 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 18:57:13 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_print(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->table.print_lock);
	printf("%ld %d %s", get_time_now() - philo->table.start_time,
		philo->philo_id, text);
	pthread_mutex_unlock(&philo->table.print_lock);
}

long	get_time_now(void)
{
	struct timeval	now;
	
	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	is_someone_dead(t_philo *philo, int next_meal, long time)
{
	if (next_meal >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->is_running = FALSE;
		pthread_mutex_unlock(&philo->table->death_lock);
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%ld %d is dead 💀", time - table->start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->table->print_lock);
		return (TRUE);
	}
	return (FALSE);
}

int	is_all_eaten(t_table *table, int all_eaten)
{
	if (table->max_meals > 0)
	{
		if (all_eaten == table->num_philos)
		{
			pthread_mutex_lock(&table->death_lock);
			table->is_running = FALSE;
			pthread_mutex_unlock(&table->death_lock);
			pthread_mutex_lock(&table->print_lock);
			printf("All philosophers have eaten %d times!", table->max_meals);
			pthread_mutex_unlock(&table->print_lock);
			return (TRUE);
		}
	}
	return (FALSE);
}

int is_simulation_over(t_table *table)
{
	int status;
	
	pthread_mutex_lock(&table->death_lock);
	status = table->is_running;
	pthread_mutex_unlock(&table->death_lock);
	return (status);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!is_simulation_over(philo->table))
	{
		//try_take_fork
		//eat (2 cases: 1 philo, more than one)
		//sleep
		//think (0, algum calculo = resto do tempo até comer / 2, 100, 500)
	}
	return (NULL);
}

void	start_monitor(t_table *table)
{
	int		i;
	int		all_eaten;
	long	now;
	long	next_meal;

	i = -1;
	all_eaten = 0;
	//wait for all ready?
	while (!is_simulation_over(table))
	{
		while (++i < table->num_philos)
		{
			pthread_mutex_lock(&table->meal_lock);
			now = get_time_now();
			next_meal = now - table->philos[i].last_meal;
			if (table->philos[i].meals_eaten == table->max_meals)
				all_eaten++;
			pthread_mutex_unlock(&table->meal_lock);
			if (is_someone_dead(table->philos[i], next_meal, now)
				|| is_all_eaten(table))
				break ;
		}
		usleep(100);
	}
	return (FALSE);
}
