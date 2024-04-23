/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:42:35 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 21:48:38 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->common->print);
	pthread_mutex_lock(&philo->common->checks);
	if (!philo->common->dead)
		printf("[%ldms] philo %d %s\n", get_time() - \
philo->common->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->common->checks);
	pthread_mutex_unlock(&philo->common->print);
}

int	eat(t_philo *philo)
{
	int	check;

	ft_print(philo, "is eating");
	check = ft_usleep(philo, philo->common->time_to_eat);
	return (check);
}

void	think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	if (philo->common->time_to_sleep < philo->common->time_to_eat)
		ft_usleep(philo, philo->common->time_to_eat - philo->common->time_to_sleep);
	else
		usleep(400);
}

int	p_sleep(t_philo *philo)
{
	int	check;

	ft_print(philo, "is sleeping");
	check = ft_usleep(philo, philo->common->time_to_sleep);
	return (check);
}

int	handle_forks(t_philo *philo)
{
	int	check;

	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->common->checks);
	if (philo->common->nb_philos == 1)
	{
		pthread_mutex_unlock(&philo->common->checks);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->common->checks);
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	check = eat(philo);
	pthread_mutex_lock(&philo->common->checks);
	philo->nb_meals++;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->common->checks);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (check);
}
