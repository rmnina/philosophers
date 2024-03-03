/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:44:41 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/03 16:51:45 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_finished(t_common *common, int i)
{
	if (common->philo_tab[i]->nb_meals == common->max_meals)
		common->finished++;
	if (common->finished == common->nb_philos)
	{
		sem_wait(common->checks);
		sem_wait(common->print);
		printf \
		("(%ldms) all philos have eaten their %d meals!! they're happy and the simulation may end\n", \
		get_time() - common->start_time, common->max_meals);
		sem_post(common->print);
		common->dead = TRUE;
		return (1);
	}
	return (0);
}

void	*controller_routine(void *tmp)
{
	t_philo 		**philo;
	
	philo = (t_philo **)tmp;
	while (1)
	{
		// sem_wait(philo->common->checks);
		// if (check_finished(philo->common, i))
		// 	return (NULL);
		if (get_time() - (*philo)->last_ate > (*philo)->common->time_to_die)
		{
			sem_post((*philo)->common->checks);
			ft_print(philo, "has died");
			(*philo)->died = TRUE;
			exit(0);
		}
		usleep(1000);
	}
}

void	*routine(t_philo **philo)
{
	// sem_wait(philo->common->checks);
	while (!(*philo)->died)
	{
		// sem_post(philo->common->checks);
		handle_forks(philo);
		if ((*philo)->common->nb_philos == 1)
			return (NULL);
		p_sleep(philo);
		think(philo);
	}
	exit(0);
}

void	start_philo(t_philo **philo)
{
	pthread_t	controller;

	if ((*philo)->id % 2 == 0)
		usleep(8000);
	pthread_create(&controller, NULL, controller_routine, philo);
	pthread_detach(controller);
	routine(philo);
	if ((*philo)->died)
		exit(0);
}

void	init_processes(t_common *common, pid_t *pid_tab)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < common->nb_philos)
	{
		pid = fork();
		if (pid == 0)
			start_philo(&common->philo_tab[i]);
		else
			pid_tab[i] = pid;
		i++;
	}
	wait_pids(common, pid_tab);
}

int main(int argc, char **argv)
{
	t_common	*common;
	pid_t		*pid_tab;

	if (!get_errors(argc, argv))
	{
		common = init_common(argv, ft_atoi(argv[1]));
		if (common == NULL)
		{
			printf("error\n");
			return (1);
		}
		pid_tab = init_pid_table(common);
		init_processes(common, pid_tab);
	}
	// free_philo(&common);
	return (0);
}