/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:42:35 by jdufour           #+#    #+#             */
/*   Updated: 2024/02/19 15:46:24 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->common->print);
	if (!philo->common->dead)
		printf("(%ldms) philo %d %s\n", get_time() - philo->common->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->common->print);
}

void	eat(t_philo *philo)
{
	ft_print(philo, "is eating");
	usleep((philo->common->time_to_eat) * 1000);
}

void	think(t_philo *philo)
{
	ft_print(philo, "is thinking");
	usleep(400);
}

void	p_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	usleep((philo->common->time_to_sleep) * 1000);
}

void	handle_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	if (philo->common->nb_philos == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	eat(philo);
	pthread_mutex_lock(&philo->common->checks);
	philo->nb_meals++;
	philo->last_ate = get_time();
	pthread_mutex_unlock(&philo->common->checks);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}