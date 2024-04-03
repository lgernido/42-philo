/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:49:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/03 09:20:05 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_parameters	*data;

	data = (t_parameters *)arg;
	printf("Je suis le moniteur, il y a %d philo\n", data->number_of_forks);
	return (0);
}

void	create_monitor(t_parameters *parameters)
{
	pthread_t	*monitor;

	monitor = (pthread_t *)malloc(sizeof(*monitor));
	if (monitor == NULL)
	{
		printf("Failed to allocate monitor thread\n");
		return ;
	}
	if (pthread_create(monitor, NULL, &monitor_routine, parameters) != 0)
	{
		printf("Failed to create monitor thread\n");
		return ;
	}
	if (pthread_join(*monitor, NULL) != 0)
	{
		printf("Failed to join monitor\n");
		return ;
	}
	printf("Moniteur termine\n");
	free(monitor);
}
