/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:02:09 by tfinni            #+#    #+#             */
/*   Updated: 2023/06/15 18:02:15 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destroy_simple(t_data *data)
{
	if (pthread_mutex_destroy(&data->food) != 0)
	{
		data->error = 2;
		return ;
	}
	if (pthread_mutex_destroy(&data->end) != 0)
	{
		data->error = 2;
		return ;
	}
	if (pthread_mutex_destroy(&data->write) != 0)
	{
		data->error = 2;
		return ;
	}
	if (pthread_mutex_destroy(&data->eat_count_mutex) != 0)
	{
		data->error = 2;
		return ;
	}
}

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->count - 1)
	{
		if (pthread_mutex_destroy(&data->fork[i]) != 0)
		{
			data->error = 2;
			return ;
		}
		i++;
	}
	i = 0;
	while (i <= data->count - 1)
	{
		if (pthread_mutex_destroy(&data->status[i]) != 0)
		{
			data->error = 2;
			return ;
		}
		i++;
	}
	ft_destroy_simple(data);
}

static void	ft_wait_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->count - 1)
	{	
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			data->error = 2;
			return ;
		}
		i++;
		if (data->count == 1)
			break ;
	}
}

static void	ft_make_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_current_time();
	while (i <= data->count - 1)
	{
		data->philo[i].last_ate = data->start;
		if (pthread_create(&data->philo[i].thread, NULL, \
		ft_start, &data->philo[i]) != 0)
		{
			data->error = 2;
			return ;
		}
		i++;
	}
	ft_checker(data);
	ft_wait_philo(data);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_read_values(argv) == 1)
		return (1);
	ft_init(&data, argv, argc);
	if (data.error == 2)
		return (1);
	if (data.error == 1)
	{
		ft_free(&data);
		return (1);
	}
	ft_make_threads(&data);
	if (data.error == 2)
	{
		ft_free(&data);
		return (1);
	}
	ft_destroy_mutex(&data);
	ft_free(&data);
	if (data.error == 2)
		return (1);
	return (0);
}
