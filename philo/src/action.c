/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:18:52 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 20:19:09 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld %d %s", get_time_now() - philo->table->start_time,
		philo->philo_id, text);
	pthread_mutex_unlock(&philo->table->print_lock);
}
