/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciegernidos <luciegernidos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:10:00 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/07 16:42:59 by luciegernid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

long	get_time(void)
{
	struct timeval	current_time;
	double			time;

	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	return (time);
}

void	clean_everything(t_parameters *parameters)
{
	(void)parameters;
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
		run_simulation(parameters);
		return (0);
	}
	else
	{
		syntax_guide();
		return (1);
	}
}
