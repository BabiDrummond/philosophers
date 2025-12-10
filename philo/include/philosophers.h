/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:42:22 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/09 21:52:47 by bmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

# define TRUE 1
# define FALSE 0

typedef struct s_table t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;
	int				philo_id;
	int				meals_eaten;
	long			last_meal;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				is_running;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t meal_lock;
}	t_table;

typedef enum e_error
{
	USAGE = 0,
	INVALID_ARGUMENT = 1,
	ALLOC = 2,
	TABLE_MUTEX = 3,
	FORKS = 4,
	CREATE_THREAD = 5,
	JOIN_THREAD = 6
}	t_error;

// Initialization
int		init_data(t_table *table, int argc, char **argv);

// Destroy
void	destroy_table_mutexes(t_table *table, int m_count);
void	destroy_forks(t_table *table, int m_count);
void	destroy_philos(t_table *table, int p_count);
void	destroy_data(t_table *table, int mutex, int forks, int philos);

// Simulation
void	*start_simulation(void *arg);

// Utils
long	get_time_now(void);
long	safe_atoi(char *str);
int		throw_error(const char *msg);
int		validate_input(int argc, char **argv);

// Monitor
void	start_monitor(t_table *table);
int 	is_simulation_over(t_table *table);

#endif