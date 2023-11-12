/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:08:07 by tfinni            #+#    #+#             */
/*   Updated: 2023/07/29 16:08:08 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	if (data->fork != NULL)
		free(data->fork);
	data->fork = NULL;
	if (data->status != NULL)
		free(data->status);
	if (data->philo != NULL)
		free(data->philo);
	data->philo = NULL;
	data->error = 1;
}

int	ft_read_values(char **argv)
{
	int	i;
	int	y;

	y = 1;
	while (argv[y])
	{
		i = 0;
		while (argv[y][i])
		{
			if (i == 0 && argv[y][0] == '+' && argv[y][1] != '\0')
				i++;
			else if (argv[y][i] < '0' || argv[y][i] > '9')
				return (1);
			else
				i++;
		}
		y++;
	}
	return (0);
}

void	ft_set_values(t_data *data, char **argv, int argc)
{
	data->error = 0;
	data->count = ft_str_to_int(argv[1]);
	data->time_die = ft_str_to_int(argv[2]);
	data->time_eat = ft_str_to_int(argv[3]);
	data->time_sleep = ft_str_to_int(argv[4]);
	if (ft_check_values(data) == 1)
	{
		return ;
	}
	data->need_eat = 1;
	if (argc == 6)
		data->need_eat = ft_str_to_int(argv[5]);
	if (data->need_eat < 1)
	{
		data->error = 2;
		return ;
	}
	if (argc == 5)
		data->need_eat = -1;
}

void	ft_eat_check(t_data *data, t_philo *philo)
{
	if (philo->times_eaten == data->need_eat)
	{
		pthread_mutex_lock(&data->eat_count_mutex);
		data->done_eating++;
		pthread_mutex_unlock(&data->eat_count_mutex);
	}
}
