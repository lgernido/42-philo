/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/03 09:19:13 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*daily_routine(void *arg)
{
	t_philo			*philosopher;
	t_parameters	*data;
	struct timeval	current_time;

	philosopher = (t_philo *)arg;
	data = philosopher->parameters;
	gettimeofday(&current_time, NULL);
	printf("%ld %d is sleeping\n", current_time.tv_usec, philosopher->position);
	usleep(data->time_to_sleep * 100);
	printf("Je suis philosophe %d\n", philosopher->position);
	return (NULL);
}
