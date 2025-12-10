/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:18:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 01:41:03 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->is_running)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		pthread_mutex_unlock(&philo->table->death_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	printf(text, get_time_now() - philo->table->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	taking_a_fork(t_philo *p, pthread_mutex_t **f, pthread_mutex_t **s)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (p->philo_id % 2 == 0)
	{
		first = *s;
		second = *f;
	}
	first = *f;
	second = *s;
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
}

void	eating(t_philo *philo, pthread_mutex_t **f, pthread_mutex_t **s)
{
}

void	sleeping(t_philo *philo)
{
	print_action(philo, "\033[34m%ld %d is sleeping 😴\033[0m\n");
	usleep(philo->table->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
}
