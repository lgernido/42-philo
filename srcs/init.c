/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:48:46 by lgernido          #+#    #+#             */
/*   Updated: 2024/03/29 09:09:44 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digits(char **argv)
{
	int	arg;
	int	index;

	arg = 1;
	while (argv[arg])
	{
		index = 0;
		while (argv[arg][index])
		{
			if (ft_isdigit(argv[arg][index]) == 0)
			{
				return (1);
			}
			else
			{
				index++;
			}
		}
		arg++;
	}
	return (0);
}

int	init_parameters(int argc, char **argv, t_parameters *parameters)
{
	if (check_digits(argv) == 0)
	{
		parameters->number_of_philosophers = ft_atoi(argv[1]);
		parameters->time_to_die = ft_atoi(argv[2]);
		parameters->time_to_eat = ft_atoi(argv[3]);
		parameters->time_to_sleep = ft_atoi(argv[4]);
		parameters->number_of_forks = parameters->number_of_philosophers;
		parameters->philo = NULL;
		if (argc == 6)
		{
			parameters->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
		}
		else
		{
			parameters->number_of_times_each_philosophers_must_eat = INT_MAX;
		}
		return (0);
	}
	else
	{
		return (1);
	}
}

void	connect_philosopher(t_philo **philo, t_philo *new_philo)
{
	t_philo	*last_philo;

	if (*philo == NULL)
	{
		*philo = new_philo;
		(*philo)->next = new_philo;
		(*philo)->prev = new_philo;
		return ;
	}
	last_philo = find_last_philo(*philo);
	last_philo->next = new_philo;
	new_philo->prev = last_philo;
	new_philo->next = *philo;
	(*philo)->prev = new_philo;
}

t_philo	*init_philosophers(t_parameters *parameters, int position)
{
	t_philo	*philosopher;

	philosopher = malloc(sizeof(*philosopher));
	if (philosopher == NULL)
	{
		printf("The philosopher can't seat\n");
		return (NULL);
	}
	philosopher->position = position + 1;
	philosopher->meal_ate = 0;
	philosopher->left_fork_available = TRUE;
	philosopher->right_fork_available = TRUE;
	philosopher->parameters = parameters;
	philosopher->next = NULL;
	philosopher->prev = NULL;
	return (philosopher);
}
