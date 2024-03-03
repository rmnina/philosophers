/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 01:25:56 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/02 20:44:10 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	(*common)->time_to_die = ft_atoi(argv[2]);
	(*common)->time_to_eat = ft_atoi(argv[3]);
	(*common)->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*common)->max_meals = ft_atoi(argv[5]);
	else
		(*common)->max_meals = -1;
    (*common)->forks = sem_open("forks", O_CREAT, 0644, 5);
	(*common)->print = sem_open("print", O_CREAT, 0644, 1);
	(*common)->checks = sem_open("checks", O_CREAT, 0644, 1);
	(*common)->dead = FALSE;
	return (0);
}

t_philo	*init_philo(int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = i;
	philo->nb_meals = 0;
	philo->last_ate = get_time();
	philo->finished = FALSE;
	philo->died = FALSE;
	return (philo);
}

t_common	*init_common(char **argv, int nb_philos)
{
	t_common		*common;
	int				i;

	i = 0;
	common = malloc(sizeof(t_common));
	if (!common)
		return (NULL);
	common->nb_philos = nb_philos;
	common->start_time = get_time();
	common->philo_tab = malloc(sizeof(t_philo) * nb_philos);
	if (!common->philo_tab)
		return (NULL);
	get_params(argv, &common);
	while (i < nb_philos)
	{
		common->philo_tab[i] = init_philo(i);
        common->philo_tab[i]->common = common;
		i++;
	}
	return (common);
}