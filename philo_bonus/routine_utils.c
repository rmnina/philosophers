/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:46:00 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/03 16:53:03 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo **philo, char *str)
{
	sem_wait((*philo)->common->print);
	if (!(*philo)->common->dead)
		printf("(%ldms) philo %d %s\n", get_time() - (*philo)->common->start_time, (*philo)->id + 1, str);
	sem_post((*philo)->common->print);
}

void	eat(t_philo **philo)
{
	if (get_time() - (*philo)->last_ate > (*philo)->common->time_to_die)
		(*philo)->common->dead = TRUE;
	sem_wait((*philo)->common->print);
	ft_print(philo, "is eating");
	sem_post((*philo)->common->print);
	usleep(((*philo)->common->time_to_eat) * 1000);
}

void	think(t_philo **philo)
{
	sem_wait((*philo)->common->print);
	ft_print(philo, "is thinking");
	sem_post((*philo)->common->print);
	usleep(400);
}

void	p_sleep(t_philo **philo)
{
	sem_wait((*philo)->common->print);
	ft_print(philo, "is sleeping");
	sem_post((*philo)->common->print);
	usleep(((*philo)->common->time_to_sleep) * 1000);
}

void	handle_forks(t_philo **philo)
{
	// printf("ICI\n");
	if (sem_wait((*philo)->common->forks) != 0)
		exit(EXIT_FAILURE);
	ft_print(philo, "has taken a fork");
	if ((*philo)->common->nb_philos == 1)
	{
		sem_post((*philo)->common->forks);
		return ;
	}
	sem_wait((*philo)->common->forks);
	ft_print(philo, "has taken a fork");
	eat(philo);
	sem_wait((*philo)->common->checks);
	(*philo)->nb_meals++;
	(*philo)->last_ate = get_time();
	sem_post((*philo)->common->checks);
	sem_post((*philo)->common->forks);
	sem_post((*philo)->common->forks);
}