/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:42:22 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/05 20:54:50 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_philo
{
	int				philo_id;
	long			start_time;
	pthread_t		thread_id;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_eat;
}	t_table;

// Validation
void	error_handler(const char *error_msg, int exit_code);
void	validate_input(int argc, char **argv);
long	ft_atol(char *str);

#endif