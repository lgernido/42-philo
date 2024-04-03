/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/03 10:26:24 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_you_dead(t_parameters *data, t_philo *philo)
{
	if (((data->current_time.tv_usec
				- philo->last_meal_time.tv_usec) > data->time_to_die)
		|| ((data->simulation_start.tv_usec
				- philo->last_meal_time.tv_usec) > data->time_to_die))
	{
		printf("%ld %d died\n", data->current_time.tv_usec, philo->position);
		return (1);
	}
	return (0);
}
void	go_sleep(t_parameters *data, t_philo *philosopher)
{
	gettimeofday(&data->current_time, NULL);
	printf("%ld %d is sleeping\n", data->current_time.tv_usec,
		philosopher->position);
	usleep(data->time_to_sleep * 100);
}

void	go_eat(t_parameters *data, t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork_available);
	pthread_mutex_lock(&philosopher->left_fork_available);
	gettimeofday(&philosopher->last_meal_time, NULL);
	printf("%ld %d is eating\n", philosopher->last_meal_time.tv_usec,
		philosopher->position);
	usleep(data->time_to_eat * 100);
	pthread_mutex_unlock(&philosopher->right_fork_available);
	pthread_mutex_unlock(&philosopher->left_fork_available);
}
void	go_think(t_parameters *data, t_philo *philosopher)
{
	gettimeofday(&data->current_time, NULL);
	printf("%ld %d is thinking\n", data->current_time.tv_usec,
		philosopher->position);
}
void	*daily_routine(void *arg)
{
	t_philo			*philosopher;
	t_parameters	*data;

	philosopher = (t_philo *)arg;
	data = philosopher->parameters;
	while (1)
	{
		go_sleep(data, philosopher);
		if (are_you_dead(data, philosopher) == 1)
			break ;
		go_eat(data, philosopher);
		if (are_you_dead(data, philosopher) == 1)
			break ;
		go_think(data, philosopher);
		if (are_you_dead(data, philosopher) == 1)
			break ;
	}
	return (NULL);
}
