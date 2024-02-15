/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:10 by jdufour           #+#    #+#             */
/*   Updated: 2024/02/11 18:08:41 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*controller_routine(void *tmp)
{
	t_philo *philo;
	philo = (t_philo *)tmp;
	
	while (1)
	{
		if (philo->last_ate > philo->common->time_to_die)
		{
			philo->died = TRUE;
			philo->common->dead = TRUE;
			return (NULL);
		}
	}
	return (NULL);
}

void	handle_forks(t_philo *philo)
{
	struct timeval tv;
	
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->common->print);
	printf("%ld : Philo %d has taken his right fork\n", gettimeofday(&tv, NULL) - philo->common->start_time, philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld : Philo %d has taken his left fork\n", gettimeofday(&tv, NULL) - philo->common->start_time, philo->id);
	printf("%ld : Philo %d has started eating\n", gettimeofday(&tv, NULL) - philo->common->start_time, philo->id);
	philo->nb_meals++;
	philo->last_ate = gettimeofday(&tv, NULL) - philo->common->start_time;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->common->print);
}

void	*routine(void *tmp)
{
	t_philo		*philo;
	pthread_t	controller;
	struct 		timeval tv;

	philo = (t_philo *)tmp;
	gettimeofday(&tv, NULL);
	if (philo->id % 2 == 1)
		usleep(500);
	pthread_create(&controller, NULL, &controller_routine, &philo);
	pthread_detach(controller);
	while (1)
	{
		if (philo->common->dead == TRUE)
		{
			pthread_mutex_lock(&philo->common->print);
			printf("%ld : Philo %d has died\n", (tv.tv_sec + tv.tv_usec) / 1000 - philo->common->start_time, philo->id);
			break ;
		}	
		handle_forks(philo);
	}
	return (NULL);
}

int	init_threads(t_common *common)
{
	int	i;

	i = 0;
	while (i < (int)common->nb_philos)
	{
		common->philo_tab[i].common = common;
		if (pthread_create(&common->philo_tab[i].thread, NULL, \
		&routine, &common->philo_tab[i]) != 0)
			return (-1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_common	*common;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (!get_errors(argc, argv))
	{
		common = init_common(argv, (int)ft_atoi(argv[1]));
		if (common == NULL)
			return (1);
		if (init_threads(common) == -1)
			return (1);
	}
	return (0);
}