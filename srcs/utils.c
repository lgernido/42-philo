/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciegernidos <luciegernidos@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:29:17 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/07 14:41:10 by luciegernid      ###   ########.fr       */
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

	if (*philo == NULL)
		return ;
	current = *philo;
	while (current != NULL && current->next != *philo)
	{
		next = current->next;
		pthread_mutex_destroy(&current->left_fork);
		pthread_mutex_destroy(&current->right_fork);
		pthread_mutex_destroy(current->dead_lock);
		pthread_mutex_destroy(current->meal_lock);
		pthread_mutex_destroy(current->print_lock);
		free(current);
		current = next;
	}
	free(current);
	*philo = NULL;
}
