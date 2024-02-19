/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:50:10 by jdufour           #+#    #+#             */
/*   Updated: 2024/02/19 15:58:04 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_finished(t_common *common, int i)
{
	if (common->philo_tab[i].nb_meals == common->max_meals)
		common->finished++;
	if (common->finished == common->nb_philos)
	{
		pthread_mutex_unlock(&common->checks);
		pthread_mutex_lock(&common->print);
		printf \
		("(%ldms) all philos have eaten their %d meals!! they're happy and the simulation may end\n", \
		get_time() - common->start_time, common->max_meals);
		pthread_mutex_unlock(&common->print);
		common->dead = TRUE;
		return (1);
	}
	return (0);
}

void	*controller_routine(void *tmp)
{
	t_common 		*common;
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
			if (get_time() - common->philo_tab[i].last_ate > common->time_to_die)
			{
				pthread_mutex_unlock(&common->checks);
				ft_print(&common->philo_tab[i], "has died");
				common->philo_tab[i].died = TRUE;
				common->dead = TRUE;
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
		usleep(8000);
	pthread_mutex_lock(&philo->common->checks);
	while (philo->common->dead == FALSE)
	{
		pthread_mutex_unlock(&philo->common->checks);
		handle_forks(philo);
		if (philo->common->nb_philos == 1)
			return (NULL);
		p_sleep(philo);
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

int main(int argc, char **argv)
{
	t_common	*common;
	int			i;

	i = 0;
	if (!get_errors(argc, argv))
	{
		common = init_common(argv, ft_atoi(argv[1]));
		if (common == NULL)
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