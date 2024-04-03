/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:56:29 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/03 10:23:39 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//==========================================================================//
/*INCLUDES*/

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

//==========================================================================//
/*STRUCTURES AND ENUMS*/

typedef enum e_bool
{
	FALSE = 1,
	TRUE = 0
}						t_bool;

typedef struct s_parameters
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosophers_must_eat;
	int					number_of_forks;
	struct s_philo		*philo;
	struct timeval		current_time;
	struct timeval		simulation_start;
}						t_parameters;

typedef struct s_philo
{
	int					position;
	int					meal_ate;
	pthread_mutex_t		left_fork_available;
	pthread_mutex_t		right_fork_available;
	pthread_t			philo;
	struct s_philo		*next;
	struct s_philo		*prev;
	struct s_parameters	*parameters;
	struct timeval		last_meal_time;
}						t_philo;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int						main(int argc, char **argv);
void					syntax_guide(void);

// init.c
int						init_parameters(int argc, char **argv,
							t_parameters *parameters);
int						check_digits(char **argv);
t_philo					*init_philosophers(t_parameters *parameters,
							int position);
void					connect_philosopher(t_philo **philo,
							t_philo *new_philo);

// threads.c
void					init_threads(t_parameters *parameters);
void					create_threads(t_parameters *parameters,
							int threads_created, pthread_t *thread);
void					join_threads(int threads_executed, int threads_created,
							pthread_t *thread);

// routine.c
void					*daily_routine(void *arg);
int						are_you_dead(t_parameters *data, t_philo *philo);
void					go_sleep(t_parameters *data, t_philo *philosopher);
void					go_eat(t_parameters *data, t_philo *philosopher);
void					go_think(t_parameters *data, t_philo *philosopher);

// monitor.c
void					create_monitor(t_parameters *parameters);
void					*monitor_routine(void *arg);

// utils.c
int						ft_atoi(const char *nptr);
int						ft_isdigit(int c);
t_philo					*find_last_philo(t_philo *philo);
void					clear_philo_list(t_philo **philo);

#endif