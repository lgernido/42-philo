/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:56:29 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/28 12:10:36 by lgernido         ###   ########.fr       */
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
/*STRUCTURES*/

typedef struct s_parameters
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosophers_must_eat;
	int				number_of_forks;
}					t_parameters;

typedef struct s_philo
{
	int				position;
	int				meal_ate;
	pthread_t		philo;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int					main(int argc, char **argv);
void				syntax_guide(void);

// init.c
int					init_parameters(int argc, char **argv,
						t_parameters *parameters);
int					check_digits(char **argv);

// threads.c
void				init_threads(t_parameters *parameters);
void				create_threads(int number_of_philo, int threads_created,
						pthread_t *thread);
void				join_threads(int threads_executed, int threads_created,
						pthread_t *thread);
void				*daily_routine(void *arg);

// utils.c
int					ft_atoi(const char *nptr);
int					ft_isdigit(int c);

#endif