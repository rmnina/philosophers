/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:00:08 by jdufour           #+#    #+#             */
/*   Updated: 2024/02/11 18:09:05 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

int	get_errors(int argc, char **argv)
{
	int	i;
	
	i = 1;
	if (argc < 5)
		ft_error("Too few arguments.\nExpected : \n \
	number_of_philosophers \n \
	time_to_die (ms) \n \
	time_to_eat (ms) \n \
	time_to_sleep (ms) \n \
	[optionnal : number_of_times_each_philosopher_must_eat]\n");
	if (argc > 6)
		ft_error("Too many arguments.\nExpected: \n \
	number_of_philosophers \n \
	time_to_die (ms) \n \
	time_to_eat (ms) \n \
	time_to_sleep (ms) \n \
	[optionnal : number_of_times_each_philosopher_must_eat]\n");
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10 || !is_num(argv[i]))
			ft_error("Error : numerical / positive values required\n");
		if (ft_atoi(argv[i]) > 2147483647)
			ft_error("Error : arg bigger than int max\n");
		i++;
	}
	return (0);
}

int	get_params(char **argv, t_common **common)
{
	int	i;
	
	i = 0;
	(*common)->time_to_die = (u_int32_t)ft_atoi(argv[2]);
	(*common)->time_to_eat = (u_int32_t)ft_atoi(argv[3]);
	(*common)->time_to_sleep = (u_int32_t)ft_atoi(argv[4]);
	if (argv[5])
		(*common)->max_meals = (u_int32_t)ft_atoi(argv[5]);
	else
		(*common)->max_meals = -1;
	(*common)->fork = malloc(sizeof(pthread_mutex_t) * (*common)->nb_philos);
	if (!(*common)->fork)
		return (-1);
	while (i < (int)(*common)->nb_philos)
		pthread_mutex_init(&(*common)->fork[i++], NULL);
	pthread_mutex_init(&(*common)->print, NULL);
	(*common)->dead = FALSE;
	return (0);
}

t_philo	init_philo(t_common *common, int i)
{
	t_philo	philo;

	philo.id = (u_int32_t)i;
	philo.nb_meals = 0;
	philo.last_ate = 0;
	philo.finished = FALSE;
	philo.died = FALSE;
	philo.right_fork = common->fork + i;
	if (i == (int)common->nb_philos - 1)
		philo.left_fork = common->fork;
	else
		philo.left_fork = common->fork + i + 1;
	return (philo);
}

t_common	*init_common(char **argv, int nb_philos)
{
	t_common		*common;
	struct timeval	tv;
	int				i;

	i = 0;
	common = malloc(sizeof(t_common));
	if (!common)
		return (NULL);
	gettimeofday(&tv, NULL);
	common->nb_philos = nb_philos;
	common->start_time = (tv.tv_sec + tv.tv_usec) / 1000;
	common->philo_tab = malloc(sizeof(t_philo) * nb_philos);
	if (!common->philo_tab)
		return (NULL);
	get_params(argv, &common);
	while (i < nb_philos)
	{
		common->philo_tab[i] = init_philo(common, i);
		i++;
	}
	return (common);
}