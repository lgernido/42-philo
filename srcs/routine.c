/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:33:42 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/28 14:12:22 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*daily_routine(void *arg)
{
	t_philo	*philosopher;
	int		position;

	position = *(int *)arg;
	philosopher = malloc(sizeof(philosopher));
	if (philosopher == NULL)
	{
		printf("Philosopher are not seated\n");
		return (NULL);
	}
	philosopher->position = position;
	philosopher->meal_ate = 0;
	printf("Je suis philosophe\nMa position est %d\nJ'ai mange %d repas\n\n",
		philosopher->position, philosopher->meal_ate);
	free(philosopher);
	free(arg);
	return (NULL);
}
