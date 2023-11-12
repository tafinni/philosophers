/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:14:21 by tfinni            #+#    #+#             */
/*   Updated: 2023/07/29 14:14:23 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_check_ending(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->end);
	if ((data->error == 0 && philo->ate_enough == 0) || philo->ate_enough == -1)
	{
		data->error = 1;
		ft_str_print("died", data, philo);
	}
	pthread_mutex_unlock(&data->end);
}

static void	ft_checker_help(t_data *data, t_philo *philo, int i, int flag)
{
	if (flag == 1)
	{
		ft_check_ending(data, &philo[i]);
		pthread_mutex_unlock(philo[i].own_status);
	}
	else if (flag == 2)
	{
		data->error = 1;
		philo[i].ate_enough = 1;
		ft_check_ending(data, &philo[i]);
	}
}

static int	ft_checker_loop(t_data *data, t_philo *philo, int i)
{
	while (1)
	{
		if (++i == data->count)
			i = 0;
		pthread_mutex_lock(philo[i].own_status);
		if (ft_current_time() - philo[i].last_ate >= data->time_die \
		&& data->error == 0)
		{
			ft_checker_help(data, philo, i, 1);
			break ;
		}
		pthread_mutex_unlock(philo[i].own_status);
		if (data->error == 1)
		{
			ft_check_ending(data, &philo[i]);
			break ;
		}
		if (data->need_eat > 0 && data->done_eating >= data->count)
		{
			ft_checker_help(data, philo, i, 2);
			break ;
		}
		usleep(50);
	}
	return (i);
}

void	ft_checker(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philo;
	i = ft_checker_loop(data, philo, -1);
	while (data->error == 0)
	{
		if (++i == data->count)
			i = 0;
		while (data->done_eating < data->count && data->error == 0)
		{
			pthread_mutex_lock(philo[i].own_status);
			if (ft_current_time() - philo[i].last_ate >= data[i].time_die \
			&& data->error == 0)
			{
				ft_check_ending(data, &philo[i]);
				pthread_mutex_unlock(philo[i].own_status);
				break ;
			}
			pthread_mutex_unlock(philo[i].own_status);
		}
		usleep(50);
		if (data->done_eating >= data->count)
			data->error = 1;
	}
}
