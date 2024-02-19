/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:36:37 by jdufour           #+#    #+#             */
/*   Updated: 2024/02/19 02:06:08 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// i = 0;
	// while (i < (*common)->nb_philos)
	// 	free((*common)->philo_tab[i].common);
	free((*common)->philo_tab);
	free(*common);
}