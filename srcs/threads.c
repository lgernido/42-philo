/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/28 12:34:03 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(int number_of_philo, int threads_created,
		pthread_t *thread)
{
	int	*safe_value;

	while (threads_created < number_of_philo)
	{
		safe_value = (int *)malloc(sizeof(int));
		if (safe_value == NULL)
		{
			printf("Failed to allocate threads\n");
			return ;
		}
		*safe_value = threads_created + 1;
		if (pthread_create(&thread[threads_created], NULL, &daily_routine,
				(void *)safe_value) != 0)
		{
			printf("Failed to create threads\n");
			return ;
		}
		printf("thread %d has started\n", threads_created + 1);
		threads_created++;
	}
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

	thread = (pthread_t *)malloc(sizeof(*thread)
			* parameters->number_of_philosophers);
	if (thread == NULL)
	{
		printf("Failed to allocate threads\n");
		return ;
	}
	threads_created = 0;
	create_threads(parameters->number_of_philosophers, threads_created, thread);
	threads_executed = 0;
	join_threads(threads_executed, parameters->number_of_philosophers, thread);
	free(thread);
}
