/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:17:16 by tfinni            #+#    #+#             */
/*   Updated: 2023/07/29 14:17:18 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_get_philos(t_data **data, int argc)
{
	int	i;

	i = 0;
	while (i <= (*data)->count - 1)
	{
		(*data)->philo[i].number = i + 1;
		if (argc == 6)
			(*data)->philo[i].times_eaten = 0;
		(*data)->philo[i].l_fork = &(*data)->fork[i];
		if (i == 0)
			(*data)->philo[i].r_fork = &(*data)->fork[(*data)->count - 1];
		else
			(*data)->philo[i].r_fork = &(*data)->fork[i - 1];
		(*data)->philo[i].datas = *data;
		(*data)->philo[i].times_eaten = 0;
		(*data)->philo[i].last_ate = 0;
		(*data)->philo[i].ate_enough = 0;
		(*data)->philo[i].own_status = &(*data)->status[i];
		i++;
	}
}

static void	ft_get_forks(t_data **data)
{
	int	i;

	i = 0;
	(*data)->fork = malloc(sizeof(pthread_mutex_t) * (*data)->count);
	if (!(*data)->fork)
	{
		(*data)->error = 1;
		return ;
	}
	while (i <= (*data)->count - 1)
	{
		if (pthread_mutex_init((&(*data)->fork[i]), NULL) != 0)
		{
			(*data)->error = 1;
			return ;
		}
		i++;
	}
}

static void	ft_get_status(t_data **data)
{
	int	i;

	i = 0;
	(*data)->status = malloc(sizeof(pthread_mutex_t) * (*data)->count);
	if (!(*data)->status)
	{
		(*data)->error = 1;
		return ;
	}
	while (i <= (*data)->count - 1)
	{
		if (pthread_mutex_init((&(*data)->status[i]), NULL) != 0)
		{
			(*data)->error = 1;
			return ;
		}
		i++;
	}
}

static void	ft_init_mutex(t_data *data)
{
	if (pthread_mutex_init((&data->food), NULL) != 0)
	{
		data->error = 2;
		return ;
	}
	if (pthread_mutex_init((&data->end), NULL) != 0)
	{
		data->error = 2;
		return ;
	}
	if (pthread_mutex_init((&data->write), NULL) != 0)
	{
		data->error = 2;
		return ;
	}
	if (pthread_mutex_init((&data->eat_count_mutex), NULL) != 0)
	{
		data->error = 2;
		return ;
	}
}

void	ft_init(t_data *data, char **argv, int argc)
{
	ft_set_values(data, argv, argc);
	if (data->error == 2)
		return ;
	ft_init_mutex(data);
	if (data->error == 2)
		return ;
	data->done_eating = 0;
	ft_get_forks(&data);
	if (data->error == 1)
		return ;
	data->philo = malloc(sizeof(t_philo) * data->count);
	if (!data->philo)
	{
		(data)->error = 1;
		return ;
	}
	ft_get_status(&data);
	if (data->error == 1)
		return ;
	ft_get_philos(&data, argc);
	if (data->error == 1)
		return ;
}
