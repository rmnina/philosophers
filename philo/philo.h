/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:01:08 by jdufour           #+#    #+#             */
/*   Updated: 2024/02/03 17:27:56 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
#include "/Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/System/Library/Frameworks/Kernel.framework/Versions/A/Headers/mach/boolean.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_common {
	u_int32_t		nb_philos;
	u_int32_t		time_to_die;
	u_int32_t		time_to_eat;
	u_int32_t		time_to_sleep;
	u_int32_t		max_meals;
	time_t			start_time;
	u_int32_t		finished;
	bool			dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	struct s_philo	*philo_tab;
}	t_common;

typedef struct s_philo
{
	pthread_t		thread;
	u_int32_t		id;
	u_int32_t		nb_meals;
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

// PARSING
int			get_errors(int argc, char **argv);
t_common	*init_common(char **argv, int nb_philos);
t_philo		init_philo(t_common *common, int i);

#endif
