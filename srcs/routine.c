/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/05 09:42:40 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_you_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->parameters->someone_is_dead == 1)
		return (pthread_mutex_unlock(&philo->dead_lock), 1);
	pthread_mutex_unlock(&philo->dead_lock);
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
	{
		pthread_mutex_lock(&philosopher->right_fork);
		if (data->number_of_philosophers == 1)
		{
			usleep(data->time_to_die);
			pthread_mutex_unlock(&philosopher->right_fork);
			return ;
		}
		gettimeofday(&data->current_time, NULL);
		printf("%ld %d had taken a fork", data->current_time.tv_usec,
			philosopher->position);
		pthread_mutex_lock(&philosopher->left_fork);
		gettimeofday(&data->current_time, NULL);
		printf("%ld %d had taken a fork", data->current_time.tv_usec,
			philosopher->position);
		philosopher->currently_eating = 1;
		gettimeofday(&philosopher->last_meal_time, NULL);
		printf("%ld %d is eating\n", philosopher->last_meal_time.tv_usec,
			philosopher->position);
		usleep(data->time_to_eat * 100);
		philosopher->meal_ate++;
		philosopher->currently_eating = 0;
		pthread_mutex_unlock(&philosopher->left_fork);
		pthread_mutex_unlock(&philosopher->right_fork);
	}
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
	int				*return_value;

	return_value = (int *)malloc(sizeof(int));
	if (return_value == NULL)
	{
		printf("Malloc error\n");
		*return_value = 1;
		return ((void *)(return_value));
	}
	*return_value = 0;
	philosopher = (t_philo *)arg;
	data = philosopher->parameters;
	while (!are_you_dead(philosopher))
	{
		go_eat(data, philosopher);
		go_think(data, philosopher);
		go_sleep(data, philosopher);
	}
	if (data->someone_is_dead == 1)
		*return_value = 1;
	return ((void *)(return_value));
}
