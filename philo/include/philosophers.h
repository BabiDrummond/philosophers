/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoreira <bmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:42:22 by bmoreira          #+#    #+#             */
/*   Updated: 2025/12/11 05:53:31 by bmoreira         ###   ########.fr       */
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

typedef enum e_lock
{
	DEATH = 0,
	PRINT = 1,
	MEAL = 2,
	LOCK_COUNT = 3,
}	t_lock;

typedef enum e_error
{
	USAGE = 0,
	ARGUMENTS = 1,
	ALLOC = 2,
	MUTEX = 3,
	FORKS = 4,
	THREADS = 5,
}	t_error;

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
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
	char			locks[LOCK_COUNT];
	t_philo			*philos;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
}	t_table;

// Initialization & Destroy
int		init_data(t_table *table, int argc, char **argv);
void	destroy_data(t_table *table, int forks, int philos);

// Action
void	wait_action(t_philo *philo, long ms);
void	taking_a_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

// Simulation
int		is_simulation_running(t_table *table);
void 	*simulation_one_philo(t_philo *philo);
void	*start_simulation(void *arg);

// Monitor
void	start_monitor(t_table *table);

// Utils
long	get_time_now(void);
long	safe_atoi(char *str);
void	safe_print(t_philo *philo, char *text);
int		throw_error(t_table *table, int forks, int philos, int error_code);
int		validate_input(int argc, char **argv);

#endif