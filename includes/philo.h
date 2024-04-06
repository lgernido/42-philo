/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:56:29 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/06 10:30:11 by lgernido         ###   ########.fr       */
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
/*COLORS*/

# define NRM "\x1B[0m"
# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"

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
	int					number_of_times_philosopher_must_eat;
	struct s_philo		*philo;
	long				current_time;
	long				simulation_start;
	int					someone_is_dead;
}						t_parameters;

typedef struct s_philo
{
	pthread_t			philo;
	int					position;
	int					meal_ate;
	int					currently_eating;
	int					dead;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		print_lock;
	struct s_philo		*next;
	struct s_philo		*prev;
	struct s_parameters	*parameters;
	long				last_meal_time;
}						t_philo;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int						main(int argc, char **argv);
void					syntax_guide(void);
void					clean_everything(t_parameters *parameters);
long					get_time(void);
int						ft_usleep(long milliseconds);

// init.c
int						init_parameters(int argc, char **argv,
							t_parameters *parameters);
int						check_digits(char **argv);
t_philo					*init_philosophers(t_parameters *parameters,
							int position);
void					connect_philosopher(t_philo **philo,
							t_philo *new_philo);

// threads.c
int						run_simulation(t_parameters *parameters);
void					thread_driver(t_parameters *parameters,
							pthread_t *thread, pthread_t *monitor);
int						join_threads(int threads_executed, int threads_created,
							pthread_t *thread, t_parameters *parameters);
void					create_threads(t_parameters *parameters,
							int threads_created, pthread_t *thread);
void					join_monitor(pthread_t *monitor,
							t_parameters *parameters);

// routine.c
void					*daily_routine(void *arg);
int						are_you_dead(t_philo *philo);
void					go_sleep(t_parameters *data, t_philo *philosopher);
void					go_eat(t_parameters *data, t_philo *philosopher);
void					go_think(t_parameters *data, t_philo *philosopher);
void					display_message(char *str, t_philo *philo,
							t_parameters *data);

// monitor.c
int						reaper_check(t_parameters *data, t_philo *philo);
pthread_t				*create_monitor(t_parameters *parameters);
void					*monitor_routine(void *arg);
int						reaper_loop(t_philo *philo);
int						did_you_eat(t_philo *philo, t_parameters *data);

// utils.c
int						ft_atoi(const char *nptr);
int						ft_isdigit(int c);
t_philo					*find_last_philo(t_philo *philo);
void					clear_philo_list(t_philo **philo);

#endif