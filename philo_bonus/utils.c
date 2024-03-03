/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdufour <jdufour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 02:22:14 by jdufour           #+#    #+#             */
/*   Updated: 2024/03/01 02:22:26 by jdufour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			time;
	
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);;
	return (time);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (i == 0 && str[i] == '+')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long int	ft_atoi(char *str)
{
	int			i;
	long int	res;

	i = 0;
	res = 0;
	while (str && str[i])
	{
		if (i == 0 && str[i] == '+')
		{
			i++;
			if (!str[i])
				break ;
		}
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str && str[size])
		size++;
	return (size);
}