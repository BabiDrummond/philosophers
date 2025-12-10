/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:18:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 01:11:08 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, char *text)
{
	int	time_action;

	pthread_mutex_lock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->is_running)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	time_action = get_time_now() - philo->table->start_time;
	printf("%ld %d %s", time_action, philo->philo_id, text);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	taking_a_fork(t_philo *philo)
{
}

void	eating(t_philo *philo)
{
}

void	sleeping(t_philo *philo)
{
}

void	thinking(t_philo *philo)
{
}
