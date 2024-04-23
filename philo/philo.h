/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:01:08 by jdufour           #+#    #+#             */
/*   Updated: 2024/04/23 21:31:58 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE 1

typedef struct s_common {
	pthread_t		controller;
	int				nb_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				max_meals;
	time_t			start_time;
	int				finished;
	bool			dead;
	pthread_mutex_t	checks;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	struct s_philo	*philo_tab;
}	t_common;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nb_meals;
	time_t			last_ate;
	bool			finished;
	bool			died;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_common	*common;
}	t_philo;

// UTILS
int			is_num(char *str);
long int	ft_atoi(char *str);
void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
time_t		get_time(void);

// PARSING
int			get_errors(int argc, char **argv);
t_common	*init_common(char **argv, int nb_philos);
t_philo		init_philo(t_common *common, int i);

// ROUTINE
void		ft_print(t_philo *philo, char *str);
int			eat(t_philo *philo);
void		think(t_philo *philo);
int			p_sleep(t_philo *philo);
int			handle_forks(t_philo *philo);
void		oops_philo_died(t_common *common, int i);
int			ft_usleep(t_philo *philo, time_t value);

// END
void		free_philo(t_common **common);

#endif
