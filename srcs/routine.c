/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/09 09:09:54 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_you_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->parameters->dead_lock);
	if (*philo->dead == 1)
	{
		return (pthread_mutex_unlock(&philo->parameters->dead_lock), 1);
	}
	pthread_mutex_unlock(&philo->parameters->dead_lock);
	return (0);
}

void	go_sleep(t_parameters *data, t_philo *philosopher)
{
	display_message("is sleeping", philosopher, data);
	ft_usleep(data->time_to_sleep);
}

void	go_eat(t_parameters *data, t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork);
	display_message("has taken a fork", philosopher, data);
	if (data->number_of_philosophers == 1)
	{
		ft_usleep(data->time_to_die);
		pthread_mutex_unlock(&philosopher->right_fork);
		return ;
	}
	pthread_mutex_lock(&philosopher->left_fork);
	display_message("has taken a fork", philosopher, data);
	philosopher->currently_eating = 1;
	display_message("is eating", philosopher, data);
	pthread_mutex_lock(&data->meal_lock);
	philosopher->last_meal_time = 0;
	philosopher->meal_ate++;
	pthread_mutex_unlock(&data->meal_lock);
	ft_usleep(data->time_to_eat);
	philosopher->currently_eating = 0;
	pthread_mutex_unlock(&philosopher->left_fork);
	pthread_mutex_unlock(&philosopher->right_fork);
}

void	go_think(t_parameters *data, t_philo *philosopher)
{
	display_message("is thinking", philosopher, data);
}

void	*daily_routine(void *arg)
{
	t_philo			*philosopher;
	t_parameters	*data;

	philosopher = (t_philo *)arg;
	data = philosopher->parameters;
	if (philosopher->position % 2 == 0)
		ft_usleep(1);
	while (!are_you_dead(philosopher))
	{
		go_eat(data, philosopher);
		go_sleep(data, philosopher);
		go_think(data, philosopher);
	}
	return (arg);
}
