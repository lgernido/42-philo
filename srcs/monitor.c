/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciegernidos <luciegernidos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:49:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/07 14:21:49 by luciegernid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	reaper_check(t_parameters *data, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(philo->meal_lock);
	current_time = get_time();
	if ((current_time - philo->last_meal_time) >= data->time_to_die
		&& philo->currently_eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->meal_lock);
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
		if (reaper_check(data, &philo[index]))
		{
			display_message("has died", &philo[index], data);
			pthread_mutex_lock(philo[0].dead_lock);
			// data->someone_is_dead = 1;
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
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
	if (data->number_of_times_philosopher_must_eat == INT_MAX)
		return (0);
	while (index < data->number_of_philosophers)
	{
		pthread_mutex_lock(philo[index].meal_lock);
		if (philo[index].meal_ate >= data->number_of_times_philosopher_must_eat)
			done_eating++;
		pthread_mutex_unlock(philo[index].meal_lock);
		index++;
	}
	if (done_eating == data->number_of_philosophers)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
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
		pthread_mutex_lock(data->philo->dead_lock);
		if (*data->philo->dead == 1)
		{
			printf("A philosopher has died. Stopping simulation.\n");
			pthread_mutex_unlock(data->philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(data->philo->dead_lock);
		printf("Monitoring philosopher state...\n");
		if (reaper_loop(data->philo) == 1 || did_you_eat(data->philo,
				data) == 1)
		{
			printf("Simulation should stop.\n");
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
