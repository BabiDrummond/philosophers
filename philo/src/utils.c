/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 01:50:24 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 21:47:44 by bmoreira         ###   ########.fr       */
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

int	throw_error(int error_code)
{
	if (error_code == USAGE)
		printf("Usage: ./philo [num_of_philosophers] "
			"[time_to_die] [time_to_eat] [time_to_sleep] "
			"[opt: num_of_times_each_philosopher_must_eat]");
	if (error_code == INVALID_ARGUMENT)
		printf("Invalid argument provided.");
	if (error_code == ALLOC)
		printf("Error allocating philos.");
	if (error_code == TABLE_MUTEX)
		printf("Error initializing table mutexes.");
	if (error_code == FORKS)
		printf("Error initializing fork mutexes.");
	if (error_code == CREATE_THREAD)
		printf("Error creating thread.");
	if (error_code == JOIN_THREAD)
		printf("Error joining thread");
	return (FALSE);
}

int	validate_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (throw_error(USAGE));
	while (argv[++i])
		if ((safe_atoi(argv[i]) <= 0 || safe_atoi(argv[i]) > INT_MAX))
			return (throw_error(INVALID_ARGUMENT));
	return (TRUE);
}
