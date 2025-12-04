/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:42:22 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/04 02:35:32 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;
}	t_philo;

typedef struct s_philos
{
	t_philo	philos[200];
	int		is_dead;
	int		is_eating;
	int		is_sleeping;
}	t_philos;

// Validation
void	error_handler(const char *error_msg, int exit_code);
void	validate_input(int argc, char **argv);
long	ft_atol(char *str);

#endif