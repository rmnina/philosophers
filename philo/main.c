/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:10 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 21:44:25 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_finished(t_common *common, int i)
{
	if (common->max_meals != -1)
	{
		if (common->philo_tab[i].nb_meals >= common->max_meals \
		&& common->philo_tab[i].finished == FALSE)
		{
			common->philo_tab[i].finished = TRUE;
			common->finished--;
		}
		if (common->finished == 0)
		{
			pthread_mutex_lock(&common->print);
			printf \
			("[%ldms] all philos have eaten their %d meals!! \
they're happy and the simulation may end\n", \
	get_time() - common->start_time, common->max_meals);
			common->dead = TRUE;
			pthread_mutex_unlock(&common->print);
			pthread_mutex_unlock(&common->checks);
			return (1);
		}
		return (0);
	}
	return (0);
}

void	*controller_routine(void *tmp)
{
	t_common		*common;
	int				i;

	common = (t_common *)tmp;
	while (1)
	{
		i = 0;
		while (i < common->nb_philos)
		{
			usleep(1000);
			pthread_mutex_lock(&common->checks);
			if (check_finished(common, i))
				return (NULL);
			if (get_time() - common->philo_tab[i].last_ate > \
			common->time_to_die)
			{
				oops_philo_died(common, i);
				return (NULL);
			}
			pthread_mutex_unlock(&common->checks);
			i++;
		}
	}
	return (NULL);
}

void	*routine(void *tmp)
{
	t_philo		*philo;

	philo = (t_philo *)tmp;
	if (philo->id % 2 == 0)
	{
		if (ft_usleep(philo, philo->common->time_to_eat))
			return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->common->checks);
		if (philo->common->dead)
		{
			pthread_mutex_unlock(&philo->common->checks);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->common->checks);
		if (handle_forks(philo) == 1)
			return (NULL);
		if (p_sleep(philo) == 1)
			return (NULL);
		think(philo);
	}
	return (NULL);
}

void	init_threads(t_common *common)
{
	int			i;

	i = 0;
	if (pthread_create(&common->controller, NULL, controller_routine, common) \
	!= 0)
		return ;
	while (i < common->nb_philos)
	{
		common->philo_tab[i].common = common;
		if (pthread_create(&common->philo_tab[i].thread, NULL, \
		routine, &common->philo_tab[i]) != 0)
		{
			printf("error\n");
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_common	*common;
	int			i;

	i = 0;
	if (!get_errors(argc, argv))
	{
		common = init_common(argv, ft_atoi(argv[1]));
		if (!common)
		{
			printf("error\n");
			return (1);
		}
		init_threads(common);
		while (i < common->nb_philos)
		{
			pthread_join(common->philo_tab[i].thread, NULL);
			i++;
		}
		pthread_join(common->controller, NULL);
	}
	free_philo(&common);
	return (0);
}
