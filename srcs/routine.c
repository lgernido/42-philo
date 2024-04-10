/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/10 10:00:08 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_parameters *data, t_philo *philosopher)
{
	display_message("is sleeping", philosopher, data);
	ft_usleep(data->time_to_sleep);
}

void	grab_forks(t_parameters *data, t_philo *philosopher)
{
	if (philosopher->position % 2 == 0)
	{
		pthread_mutex_lock(&philosopher->prev->my_fork);
		display_message("has taken a fork", philosopher, data);
		pthread_mutex_lock(&philosopher->my_fork);
		display_message("has taken a fork", philosopher, data);
	}
	else
	{
		pthread_mutex_lock(&philosopher->my_fork);
		display_message("has taken a fork", philosopher, data);
		pthread_mutex_lock(&philosopher->prev->my_fork);
		display_message("has taken a fork", philosopher, data);
	}
	pthread_mutex_lock(&data->meal_lock);
	philosopher->last_meal_time = get_time();
	pthread_mutex_unlock(&data->meal_lock);
}

void	go_eat(t_parameters *data, t_philo *philosopher)
{
	if (data->time_to_die < data->time_to_sleep)
		go_think(data, philosopher);
	if (data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philosopher->my_fork);
		ft_usleep(data->time_to_die);
		pthread_mutex_unlock(&philosopher->my_fork);
		return ;
	}
	grab_forks(data, philosopher);
	if (!are_you_dead(data))
	{
		pthread_mutex_lock(&data->meal_lock);
		philosopher->currently_eating = 1;
		display_message("is eating", philosopher, data);
		philosopher->meal_ate++;
		pthread_mutex_unlock(&data->meal_lock);
		ft_usleep(data->time_to_eat);
		pthread_mutex_lock(&data->meal_lock);
		philosopher->currently_eating = 0;
		pthread_mutex_unlock(&data->meal_lock);
	}
	pthread_mutex_unlock(&philosopher->my_fork);
	pthread_mutex_unlock(&philosopher->prev->my_fork);
}

void	go_think(t_parameters *data, t_philo *philosopher)
{
	if (!are_you_dead(data))
		display_message("is thinking", philosopher, data);
	if (data->time_to_eat >= data->time_to_sleep)
		ft_usleep(data->time_to_eat - data->time_to_sleep + 1);
}

void	*daily_routine(void *arg)
{
	t_philo			*philosopher;
	t_parameters	*data;

	philosopher = (t_philo *)arg;
	data = philosopher->parameters;
	if (philosopher->position % 2 == 0)
		ft_usleep(1);
	while (!are_you_dead(data))
	{
		go_eat(data, philosopher);
		go_sleep(data, philosopher);
		go_think(data, philosopher);
	}
	return (arg);
}
