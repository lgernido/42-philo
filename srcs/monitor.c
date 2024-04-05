/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:49:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/05 09:44:06 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	reaper_check(t_parameters *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if ((((data->current_time.tv_usec
					- philo->last_meal_time.tv_usec) > data->time_to_die)
			|| ((data->simulation_start.tv_usec
					- philo->last_meal_time.tv_usec) > data->time_to_die))
		&& philo->currently_eating == 0)
	{
		data->someone_is_dead = 1;
		printf("%ld %d died\n", data->current_time.tv_usec, philo->position);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (0);
	}
}

int	reaper_loop(t_philo *philo)
{
	int				index;
	t_parameters	*data;

	data = philo->parameters;
	index = 0;
	while (index < data->number_of_philosophers)
	{
		if (reaper_check(data, philo))
		{
			pthread_mutex_lock(&philo->dead_lock);
			philo->dead = 1;
			pthread_mutex_unlock(&philo->dead_lock);
			return (1);
		}
		philo = philo->next;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_parameters	*data;

	data = (t_parameters *)arg;
	while (1)
	{
		if (reaper_loop(data->philo) == 1)
			break ;
	}
	return (0);
}

pthread_t	*create_monitor(t_parameters *parameters)
{
	pthread_t	*monitor;

	monitor = (pthread_t *)malloc(sizeof(*monitor));
	if (monitor == NULL)
	{
		printf("Failed to allocate monitor thread\n");
		return (NULL);
	}
	if (pthread_create(monitor, NULL, &monitor_routine, parameters) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (NULL);
	}
	return (monitor);
}

void	join_monitor(pthread_t *monitor)
{
	if (pthread_join(*monitor, NULL) != 0)
	{
		printf("Failed to join monitor\n");
		return ;
	}
	printf("Moniteur termine\n");
	free(monitor);
}
