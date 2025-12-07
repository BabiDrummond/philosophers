/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:42:22 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/06 22:29:47 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define SUCCESS 1
# define FAILURE 0

typedef struct s_table t_table;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	t_philo	*philos;
	long	start_time;
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_of_eat;
}	t_table;

// Validation
void	clean_all(t_table *table, int m_count);
int		throw_error(t_table *table, int m_count, const char *msg);
int		validate_input(int argc, char **argv);
int		init_data(t_table *table, int argc, char **argv);
long	ft_atol(char *str);

#endif