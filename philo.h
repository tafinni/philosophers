/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:04:33 by tfinni            #+#    #+#             */
/*   Updated: 2023/06/15 18:04:36 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*own_status;
	int				times_eaten;
	int				ate_enough;
	long long int	last_ate;
	struct s_data	*datas;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*status;
	pthread_mutex_t	food;
	pthread_mutex_t	end;
	pthread_mutex_t	write;
	pthread_mutex_t	eat_count_mutex;
	long long int	start;
	int				*eating;
	int				count;
	long long int	time_die;
	long long int	time_eat;
	long long int	time_sleep;
	int				need_eat;
	int				done_eating;
	int				error;
	t_philo			*philo;
}	t_data;

int				ft_digit_check(int c);
void			ft_free(t_data *data);
void			ft_set_values(t_data *data, char **argv, int argc);
void			ft_checker(t_data *data);
void			ft_init(t_data *data, char **argv, int argc);
void			*ft_start(void *arg);
int				ft_check_values(t_data *data);
long long int	ft_str_to_int(const char *str);
void			ft_str_print(char *str, t_data *data, t_philo *philo);
long long int	ft_current_time(void);
void			ft_eat_check(t_data *data, t_philo *philo);
int				ft_read_values(char **argv);

#endif
