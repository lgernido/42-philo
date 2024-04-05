/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/05 14:17:53 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_you_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->parameters->someone_is_dead == 1)
	{
		pthread_mutex_unlock(&philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->dead_lock);
	return (0);
}

void	go_sleep(t_parameters *data, t_philo *philosopher)
{
	printf(BLU "%ld %d is sleeping\n", (get_time() - data->simulation_start),
		philosopher->position);
	ft_usleep(data->time_to_sleep);
}

void	go_eat(t_parameters *data, t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork);
	if (data->number_of_philosophers == 1)
	{
		usleep(data->time_to_die);
		pthread_mutex_unlock(&philosopher->right_fork);
		return ;
	}
	printf(CYN "%ld %d has taken a fork\n", (get_time()
			- data->simulation_start), philosopher->position);
	pthread_mutex_lock(&philosopher->left_fork);
	printf(CYN "%ld %d has taken a fork\n", (get_time()
			- data->simulation_start), philosopher->position);
	philosopher->currently_eating = 1;
	philosopher->last_meal_time = (get_time() - data->simulation_start);
	printf(MAG "%ld %d is eating\n", philosopher->last_meal_time,
		philosopher->position);
	ft_usleep(data->time_to_eat);
	philosopher->meal_ate++;
	philosopher->currently_eating = 0;
	pthread_mutex_unlock(&philosopher->left_fork);
	pthread_mutex_unlock(&philosopher->right_fork);
}

void	go_think(t_parameters *data, t_philo *philosopher)
{
	printf(GRN "%ld %d is thinking\n", (get_time() - data->simulation_start),
		philosopher->position);
}

void	*daily_routine(void *arg)
{
	t_philo			*philosopher;
	t_parameters	*data;

	philosopher = (t_philo *)arg;
	data = philosopher->parameters;
	while (!are_you_dead(philosopher))
	{
		go_eat(data, philosopher);
		go_sleep(data, philosopher);
		go_think(data, philosopher);
	}
	return (arg);
}
