/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:36:37 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 21:45:14 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	oops_philo_died(t_common *common, int i)
{
	pthread_mutex_unlock(&common->checks);
	ft_print(&common->philo_tab[i], "died");
	pthread_mutex_lock(&common->checks);
	common->philo_tab[i].died = TRUE;
	common->dead = TRUE;
	pthread_mutex_unlock(&common->checks);
}

int	ft_usleep(t_philo *philo, time_t value)
{
	time_t	current;
	time_t	time_end;

	current = get_time();
	time_end = get_time() + value;
	while (current < time_end)
	{
		usleep(300);
		current = get_time();
		pthread_mutex_lock(&philo->common->checks);
		if (philo->common->dead == TRUE || philo->died == TRUE)
		{
			pthread_mutex_unlock(&philo->common->checks);
			return (1);
		}
		pthread_mutex_unlock(&philo->common->checks);
	}
	return (0);
}

void	free_philo(t_common **common)
{
	int	i;

	i = 0;
	while (i < (*common)->nb_philos)
	{
		pthread_mutex_destroy(&(*common)->fork[i]);
		i++;
	}
	free((*common)->fork);
	pthread_mutex_destroy(&(*common)->print);
	pthread_mutex_destroy(&(*common)->checks);
	free((*common)->philo_tab);
	free(*common);
}
