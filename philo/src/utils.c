/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:50:24 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/11 21:55:41 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time_now(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

long	safe_atoi(char *str)
{
	long	num;
	int		negative;

	num = 0;
	negative = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			negative *= -1;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return ((long) INT_MAX + 1);
		num = (num * 10) + *str++ - 48;
		if ((num > INT_MAX && negative == 1)
			|| (num > (long) INT_MAX + 1 && negative == -1))
			return ((long) INT_MAX + 1);
	}
	return (num * negative);
}

void	safe_print(t_philo *philo, char *text)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (is_simulation_running(philo->table))
		printf(text, get_time_now() - philo->table->start_time,
			philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_lock);
}

int	throw_error(t_table *table, int forks, int philos, int error_code)
{
	if (error_code == USAGE)
		printf("Usage: ./philo [num_of_philosophers] "
			"[time_to_die] [time_to_eat] [time_to_sleep] "
			"[opt: num_of_times_each_philosopher_must_eat]\n");
	if (error_code == ARGUMENTS)
		printf("Invalid argument provided.\n");
	if (error_code == ALLOC)
		printf("Error allocating philos.\n");
	if (error_code == MUTEX)
		printf("Error initializing table mutexes.\n");
	if (error_code == FORKS)
		printf("Error initializing fork mutexes.\n");
	if (error_code == THREADS)
		printf("Error creating thread.\n");
	destroy_data(table, forks, philos);
	return (FALSE);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (throw_error(NULL, 0, 0, USAGE));
	while (argv[++i])
		if ((safe_atoi(argv[i]) <= 0 || safe_atoi(argv[i]) > INT_MAX))
			return (throw_error(NULL, 0, 0, ARGUMENTS));
	return (TRUE);
}
