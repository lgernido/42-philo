/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/03 10:24:26 by lgernido         ###   ########.fr       */
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

void	join_threads(int threads_executed, int threads_created,
		pthread_t *thread)
{
	while (threads_executed < threads_created)
	{
		if (pthread_join(thread[threads_executed], NULL) != 0)
		{
			printf("Failed to join threads\n");
			return ;
		}
		printf("thread %d is over\n", threads_executed + 1);
		threads_executed++;
	}
}

void	init_threads(t_parameters *parameters)
{
	int			threads_created;
	int			threads_executed;
	pthread_t	*thread;

	pthread_mutex_init(&parameters->philo->left_fork_available, NULL);
	pthread_mutex_init(&parameters->philo->right_fork_available, NULL);
	thread = (pthread_t *)malloc(sizeof(*thread)
			* parameters->number_of_philosophers);
	if (thread == NULL)
	{
		printf("Failed to allocate threads\n");
		return ;
	}
	threads_created = 0;
	gettimeofday(&parameters->simulation_start, NULL);
	create_threads(parameters, threads_created, thread);
	threads_executed = 0;
	join_threads(threads_executed, parameters->number_of_philosophers, thread);
	pthread_mutex_destroy(&parameters->philo->left_fork_available);
	pthread_mutex_destroy(&parameters->philo->right_fork_available);
	free(thread);
}
