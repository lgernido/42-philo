/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:10:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/10 10:36:56 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(50);
	return (0);
}

long	get_time(void)
{
	struct timeval	current_time;
	long			time;

	if (gettimeofday(&current_time, NULL) == -1)
		printf("Clock error\n");
	time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return (time);
}

int	are_you_dead(t_parameters *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->someone_is_dead == 1)
	{
		return (pthread_mutex_unlock(&data->dead_lock), 1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	clean_everything(t_parameters *parameters)
{
	(void)parameters;
	if (parameters->philo)
		clear_philo_list(&parameters->philo);
	pthread_mutex_destroy(&parameters->meal_lock);
	pthread_mutex_destroy(&parameters->dead_lock);
	pthread_mutex_destroy(&parameters->print_lock);
	free(parameters);
}

int	main(int argc, char **argv)
{
	t_parameters	*parameters;
	int				philo_seated;

	philo_seated = 0;
	parameters = malloc(sizeof(*parameters));
	if (!parameters)
		return (1);
	if (argc >= 5 && argc <= 6 && init_parameters(argc, argv, parameters) == 0
		&& check_input(parameters) == 0)
	{
		while (philo_seated < parameters->number_of_philosophers)
		{
			connect_philosopher(&parameters->philo,
				init_philosophers(parameters, philo_seated));
			philo_seated++;
		}
		run_simulation(parameters);
		clean_everything(parameters);
		return (0);
	}
	else
	{
		printf("Syntax error\n");
		return (1);
	}
}
