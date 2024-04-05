/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:10:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/05 10:42:05 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_everything(t_parameters *parameters)
{
	if (parameters->philo)
		clear_philo_list(&parameters->philo);
	free(parameters);
}

void	syntax_guide(void)
{
	printf("\nSyntax error\n");
	printf("----------------------------------------------------------------");
	printf("------------------------------------------------------------\n");
	printf("./philo [number_of_philosphers] [time_to_die] [time_to_eat] ");
	printf("[time_to_sleep] (number_of_times_each_philosophers_must_eat)\n\n");
	printf("All the time arguments are in milliseconds\n");
	printf("Last argument is optionnal\n");
	printf("-----------------------------------------------------------------");
	printf("-----------------------------------------------------------\n");
}

int	main(int argc, char **argv)
{
	t_parameters	*parameters;
	int				philo_seated;

	philo_seated = 0;
	parameters = malloc(sizeof(*parameters));
	if (argc >= 5 && argc <= 6 && init_parameters(argc, argv, parameters) == 0)
	{
		while (philo_seated < parameters->number_of_philosophers)
		{
			connect_philosopher(&parameters->philo,
				init_philosophers(parameters, philo_seated));
			philo_seated++;
		}
		init_threads(parameters);
		return (0);
	}
	else
	{
		syntax_guide();
		return (1);
	}
}
