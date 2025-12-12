/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:18:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/11 23:00:54 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_action(t_philo *philo, long ms)
{
	long	start;

	start = get_time_now();
	while ((get_time_now() - start) < ms)
	{
		if (!is_simulation_running(philo->table))
			break ;
		usleep(100);
	}
}

void	taking_a_fork(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (!is_simulation_running(philo->table))
		return ;
	first = &philo->fork_r;
	second = philo->fork_l;
	if (philo->philo_id % 2 == 0)
	{
		first = philo->fork_l;
		second = &philo->fork_r;
	}
	pthread_mutex_lock(first);
	safe_print(philo, "\033[93m%ld %d has taken a fork 🍴\033[0m\n");
	pthread_mutex_lock(second);
	safe_print(philo, "\033[93m%ld %d has taken a fork 🍴\033[0m\n");
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal = get_time_now();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_lock);
	safe_print(philo, "\033[95m%ld %d is eating 🍝\033[0m\n");
	wait_action(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	sleeping(t_philo *philo)
{
	safe_print(philo, "\033[34m%ld %d is sleeping 😴\033[0m\n");
	wait_action(philo, philo->table->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	int	think_time;

	pthread_mutex_lock(&philo->table->meal_lock);
	think_time = (philo->table->time_to_die
			- (get_time_now() - philo->last_meal)) / 2;
	pthread_mutex_unlock(&philo->table->meal_lock);
	if (think_time < 0)
		think_time = 0;
	if (think_time > 500)
		think_time = 200;
	safe_print(philo, "\033[97m%ld %d is thinking 💭\033[0m\n");
	wait_action(philo, think_time);
}
