/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/03 14:02:21 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return ;
		}
		printf("thread %d has started\n", threads_created + 1);
		current = current->next;
		threads_created++;
	}
	create_monitor(parameters);
}

int	join_threads(int threads_executed, int threads_created, pthread_t *thread,
		int *return_value)
{
	while (threads_executed < threads_created)
	{
		if (pthread_join(thread[threads_executed], (void **)&return_value) != 0)
		{
			printf("Failed to join threads\n");
			return (1);
		}
		printf("thread %d is over\n", threads_executed + 1);
		threads_executed++;
	}
	if (*return_value == 1)
		return (1);
	else
		return (0);
}
int	thread_driver(t_parameters *parameters, int *return_value,
		pthread_t *thread)
{
	int	threads_created;
	int	threads_executed;

	pthread_mutex_init(&parameters->mutex, NULL);
	threads_created = 0;
	create_threads(parameters, threads_created, thread);
	threads_executed = 0;
	if (join_threads(threads_executed, parameters->number_of_philosophers,
			thread, return_value) == 1)
	{
		free(return_value);
		free(thread);
		pthread_mutex_destroy(&parameters->mutex);
		return (1);
	}
	else
	{
		free(return_value);
		free(thread);
		pthread_mutex_destroy(&parameters->mutex);
		return (0);
	}
}

int	init_threads(t_parameters *parameters)
{
	int			*return_value;
	pthread_t	*thread;

	return_value = NULL;
	thread = (pthread_t *)malloc(sizeof(*thread)
			* parameters->number_of_philosophers);
	if (thread == NULL)
	{
		printf("Failed to allocate threads\n");
		return (1);
	}
	if (thread_driver(parameters, return_value, thread) == 1)
		return (1);
	else
		return (0);
}
