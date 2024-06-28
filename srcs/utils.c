/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:31:30 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/21 07:08:19 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	long	nbr;

	i = 0;
	nbr = 0;
	if (!nptr)
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nbr != ((nbr * 10) + (nptr[i] - 48)) / 10)
			return (0);
		nbr = (nbr * 10) + (nptr[i] - 48);
		i++;
	}
	if (nbr > 2147483647)
		return (0);
	return ((int)nbr);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_msg(char *str, t_data *data, t_philos *philo, bool death)
{
	if (!data || !str || !philo)
		return ;
	pthread_mutex_lock(&data->mutex_time);
	data->current_time = get_current_time();
	pthread_mutex_unlock(&data->mutex_time);
	pthread_mutex_lock(&data->mutex_printf);
	pthread_mutex_lock(&data->mutex_time);
	pthread_mutex_lock(&data->mutex_death);
	if (!data->death)
		printf("%ld %d %s\n", (data->current_time - data->start_time),
			philo->index, str);
	if (death)
		data->death = true;
	pthread_mutex_unlock(&data->mutex_death);
	pthread_mutex_unlock(&data->mutex_time);
	pthread_mutex_unlock(&data->mutex_printf);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&data->mutex_death);
		if (data->death)
		{
			pthread_mutex_unlock(&data->mutex_death);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_death);
		usleep(500);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
