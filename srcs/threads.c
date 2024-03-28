/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/28 11:33:28 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*daily_routine(void *arg)
{
	t_philo	*philosopher;
	int		position;

	position = *(int *)arg;
	philosopher = malloc(sizeof(t_philo));
	philosopher->position = position;
	philosopher->meal_ate = 0;
	printf("Je suis philosophe\nMa position est %d\nJ'ai mange %d repas\n\n",
		philosopher->position, philosopher->meal_ate);
	free(philosopher);
	free(arg);
	return (NULL);
}

void	init_threads(t_parameters *parameters)
{
	int			threads_created;
	int			threads_executed;
	int			*safe_value;
	pthread_t	*thread;

	thread = (pthread_t *)malloc(sizeof(*thread)
			* parameters->number_of_philosophers);
	threads_created = 0;
	while (threads_created < parameters->number_of_philosophers)
	{
		safe_value = (int *)malloc(sizeof(int));
		*safe_value = threads_created + 1;
		pthread_create(&thread[threads_created], NULL, &daily_routine,
			safe_value);
		printf("thread %d has started\n", *safe_value);
		threads_created++;
	}
	threads_executed = 0;
	while (threads_executed < threads_created)
	{
		pthread_join(thread[threads_executed], NULL);
		printf("thread %d is over\n", threads_executed + 1);
		threads_executed++;
	}
	free(thread);
}
