/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:19:03 by tfinni            #+#    #+#             */
/*   Updated: 2023/07/29 14:19:05 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_wait_time(t_data *data, int time)
{
	long long int	done;

	done = ft_current_time() + time;
	while (1)
	{
		if (ft_current_time() >= done || data->error == 1)
			break ;
		usleep(500);
	}
}

static int	ft_left_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (data->error == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	ft_str_print("has taken a fork", data, philo);
	if (data->error == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	if (data->count < 2)
	{	
		philo->ate_enough = -1;
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	return (0);
}

static int	ft_right_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (data->error == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	ft_str_print("has taken a fork", data, philo);
	if (data->error == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

static void	ft_eat(t_data *data, t_philo *philo)
{
	if (data->error == 1 || ft_left_fork(data, philo) == 1)
		return ;
	if (data->error == 1 || ft_right_fork(data, philo) == 1)
		return ;
	pthread_mutex_lock(philo->own_status);
	pthread_mutex_lock(&data->food);
	if (data->error == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&data->food);
		pthread_mutex_unlock(philo->own_status);
		return ;
	}
	ft_str_print("is eating", data, philo);
	philo->last_ate = ft_current_time();
	pthread_mutex_unlock(&data->food);
	pthread_mutex_unlock(philo->own_status);
	ft_wait_time(data, data->time_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_eat_check(data, philo);
}

void	*ft_start(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) arg;
	data = philo->datas;
	if (philo->number % 2)
		ft_wait_time(data, data->time_eat / 2);
	while (1)
	{
		ft_eat(data, philo);
		if (data->error == 1 || (data->need_eat != -1 && \
		philo->times_eaten >= data->need_eat) \
		|| philo->ate_enough == -1)
			break ;
		ft_str_print("is sleeping", data, philo);
		ft_wait_time(data, data->time_sleep);
		if (data->error == 1)
			break ;
		ft_str_print("is thinking", data, philo);
	}
	return (NULL);
}
