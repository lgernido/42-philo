/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:49:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/10 08:52:46 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(char *str, t_philo *philo, t_parameters *data)
{
	long	current_time;

	pthread_mutex_lock(&data->print_lock);
	current_time = get_time() - data->simulation_start;
	if (!are_you_dead(data))
		printf("%ld %d %s\n", current_time, philo->position, str);
	pthread_mutex_unlock(&data->print_lock);
}

int	reaper_check(t_parameters *data, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&data->meal_lock);
	current_time = get_time();
	if ((current_time - philo->last_meal_time) >= data->time_to_die
		&& philo->currently_eating == 0)
	{
		pthread_mutex_unlock(&data->meal_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->meal_lock);
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
		if (reaper_check(data, philo) == 1)
		{
			display_message("has died", philo, data);
			pthread_mutex_lock(&data->dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		philo = philo->next;
		index++;
	}
	return (0);
}

int	did_you_eat(t_philo *philo, t_parameters *data)
{
	int	index;
	int	done_eating;

	index = 0;
	done_eating = 0;
	if (data->number_of_times_philosopher_must_eat == -1)
		return (0);
	while (index < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (philo->meal_ate >= data->number_of_times_philosopher_must_eat)
			done_eating++;
		pthread_mutex_unlock(&data->meal_lock);
		philo = philo->next;
		index++;
	}
	if (done_eating == data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_parameters	*data;

	data = (t_parameters *)arg;
	while (1)
	{
		if (reaper_loop(data->philo) == 1 || did_you_eat(data->philo,
				data) == 1)
		{
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
