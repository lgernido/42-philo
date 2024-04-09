/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:29:17 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/09 14:56:42 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	write_nb(const char *nptr, int *i)
{
	int	nb;

	nb = 0;
	while (ft_isdigit(nptr[*i]))
	{
		nb = nb * 10 + (nptr[*i] - '0');
		(*i)++;
	}
	return (nb);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	neg;
	int	sign;

	i = 0;
	sign = 0;
	neg = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg++;
		sign++;
		i++;
	}
	nb = write_nb(nptr, &i);
	if (neg == 1)
		nb = -nb;
	if (sign > 1)
		return (0);
	return (nb);
}

t_philo	*find_last_philo(t_philo *philo)
{
	t_philo	*current;

	if (!philo)
		return (NULL);
	current = philo;
	while (current->next != philo)
		current = current->next;
	return (current);
}

void	clear_philo_list(t_philo **philo)
{
	t_philo	*current;
	t_philo	*next;

	current = *philo;
	while (current != NULL)
	{
		next = current->next;
		pthread_mutex_destroy(&current->my_fork);
		free(current);
		current = next;
		if (current == *philo)
		{
			break ;
		}
	}
	*philo = NULL;
}

int	are_you_dead(t_parameters *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->someone_is_dead == 1)
	{
		return (pthread_mutex_unlock(&data->dead_lock), 1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}
