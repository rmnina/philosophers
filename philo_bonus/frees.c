/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:28:03 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/03 17:01:37 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

pid_t	*init_pid_table(t_common *common)
{
	int		i;
	pid_t	*pid_tab;

	i = 0;
	pid_tab = malloc(sizeof(pid_t) * common->nb_philos);
	if (!pid_tab)
		return (NULL);
	while (i < common->nb_philos)
	{
		pid_tab[i] = -1;
		i++;
	}
	return (pid_tab);
}

// void	wait_pids(t_common *common, pid_t *pid_tab)
// {
// 	int	status;
	
// 	(void)common;
// 	(void)pid_tab;
// 	if (waitpid(0, &status, 0) > 0)
// 		exit(0);
// }

void	free_philo(t_common **common)
{
    int	i;
	
	i = 0;
	sem_close((*common)->forks);
	sem_close((*common)->print);
	sem_close((*common)->checks);
	while (i < (*common)->nb_philos)
		free((*common)->philo_tab[i]);
	free((*common)->philo_tab);
	free(*common);
}

void	wait_pids(t_common *common, pid_t *pid_tab)
{
	int	status;
	
	(void)common;
	(void)pid_tab;
	if (waitpid(0, &status, 0) > 0)
		exit(0);
}