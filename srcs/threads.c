/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:58 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/27 16:15:52 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*daily_routine(void *arg)
{
	t_philo	*philosopher;
	int		position;

	position = *(int *)arg;
	free(arg);
	philosopher = malloc(sizeof(philosopher));
	philosopher->position = position;
	philosopher->meal_ate = 0;
	printf("je suis philosophe\n ma position est %d\nj'ai mange %d repas\n",
		philosopher->position, philosopher->meal_ate);
	free(philosopher);
	return (NULL);
}

void	init_threads(t_parameters *parameters)
{
	int			threads_created;
	int			threads_executed;
	int			*safe_value;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * parameters->number_of_philosophers);
	threads_created = 1;
	safe_value = malloc(sizeof(int));
	while (threads_created <= parameters->number_of_philosophers)
	{
		*safe_value = threads_created;
		pthread_create(&thread[threads_created], NULL, &daily_routine,
			safe_value);
		printf("thread %d has started\n", threads_created);
		threads_created++;
	}
	threads_executed = 1;
	while (threads_executed < threads_created)
	{
		pthread_join(thread[threads_executed], NULL);
		printf("thread %d is over\n", threads_executed);
		threads_executed++;
	}
}
