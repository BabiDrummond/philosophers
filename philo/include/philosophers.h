/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:42:22 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/10 00:36:24 by bmoreira         ###   ########.fr       */
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

typedef enum e_locks
{
	DEATH = 0,
	PRINT = 1,
	MEAL = 2,
	MAX = 3,
}	t_locks;


typedef enum e_error
{
	USAGE = 0,
	ARGUMENTS = 1,
	ALLOC = 2,
	MUTEX = 3,
	FORKS = 4,
	THREADS = 5,
}	t_error;

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
	char			locks[MAX];
	t_philo			*philos;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t meal_lock;
}	t_table;

// Initialization & Destroy
int		init_data(t_table *table, int argc, char **argv);
void	destroy_data(t_table *table, int forks, int philos);

// Simulation
void	*start_simulation(void *arg);

// Utils
long	get_time_now(void);
long	safe_atoi(char *str);
int		throw_error(t_table *table, int forks, int philos, int error_code);
int		validate_input(int argc, char **argv);

// Monitor
void	start_monitor(t_table *table);
int 	is_simulation_running(t_table *table);

#endif