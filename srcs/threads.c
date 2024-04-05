/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/05 12:54:45 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_monitor(pthread_t *monitor, t_parameters *parameters)
{
	if (pthread_join(*monitor, NULL) != 0)
	{
		printf("Failed to join monitor\n");
		clean_everything(parameters);
		return ;
	}
	free(monitor);
}

void	create_threads(t_parameters *parameters, int threads_created,
		pthread_t *thread)
{
	t_philo	*current;

	current = parameters->philo;
	while (threads_created < parameters->number_of_philosophers)
	{
		if (pthread_create(&thread[threads_created], NULL, &daily_routine,
				(void *)current) != 0)
		{
			printf("Failed to create threads\n");
			clean_everything(parameters);
			return ;
		}
		current = current->next;
		threads_created++;
	}
}

int	join_threads(int threads_executed, int threads_created, pthread_t *thread,
		t_parameters *parameters)
{
	while (threads_executed < threads_created)
	{
		if (pthread_join(thread[threads_executed], NULL) != 0)
		{
			printf("Failed to join threads\n");
			clean_everything(parameters);
			return (1);
		}
		threads_executed++;
	}
	return (0);
}

void	thread_driver(t_parameters *parameters, pthread_t *thread,
		pthread_t *monitor)
{
	int	threads_created;
	int	threads_executed;

	threads_created = 0;
	create_threads(parameters, threads_created, thread);
	monitor = create_monitor(parameters);
	threads_executed = 0;
	join_threads(threads_executed, parameters->number_of_philosophers, thread,
		parameters);
	join_monitor(monitor, parameters);
	free(thread);
}

int	run_simulation(t_parameters *parameters)
{
	int			*return_value;
	pthread_t	*thread;
	pthread_t	*monitor;

	return_value = NULL;
	monitor = NULL;
	thread = (pthread_t *)malloc(sizeof(*thread)
			* parameters->number_of_philosophers);
	if (thread == NULL)
	{
		printf("Failed to allocate threads\n");
		clean_everything(parameters);
		return (1);
	}
	thread_driver(parameters, thread, monitor);
	return (0);
}
