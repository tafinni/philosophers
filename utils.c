/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:21:13 by tfinni            #+#    #+#             */
/*   Updated: 2023/07/29 14:21:15 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_current_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	ft_str_print(char *str, t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->write);
	printf("%lld %d %s\n", ft_current_time() - data->start, philo->number, str);
	pthread_mutex_unlock(&data->write);
}

int	ft_digit_check(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

long long int	ft_str_to_int(const char *str)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*str < 14 && *str > 8) || (*str == 32))
			str++;
	if (*str == '-' || *str == '+')
	{			
		if (str[0] == '-')
			sign = -sign;
		str++;
	}
	if (*str < 48 || *str > 57)
		return (0);
	while (*str != '\0' && ft_digit_check((int)*str) > 0)
	{
		if ((*str >= 48) && (*str <= 57))
			result = result * 10 + *str - 48;
		str++;
	}
	return (result * sign);
}

int	ft_check_values(t_data *data)
{
	if (data->count < 1 || data->count > 200)
		data->error = 2;
	if (data->time_die < 60 || data->time_die > 2147483647)
		data->error = 2;
	if (data->time_eat < 60 || data->time_eat > 2147483647)
		data->error = 2;
	if (data->time_sleep < 60 || data->time_sleep > 2147483647)
		data->error = 2;
	if (data->error == 2)
		return (1);
	else
		return (0);
}
