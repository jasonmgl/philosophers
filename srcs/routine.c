/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:05:17 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/21 07:08:19 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_data *data, t_philos *current_philo)
{
	if (!current_philo->thinking)
	{
		print_msg("is thinking", data, current_philo, false);
		current_philo->thinking = true;
	}
}

static void	sleeping(t_data *data, t_philos *current_philo)
{
	print_msg("is sleeping", data, current_philo, false);
	ft_usleep(data->info->sleep_time, data);
	thinking(data, current_philo);
}

static void	eating(t_data *data, t_philos *current_philo)
{
	print_msg("is eating", data, current_philo, false);
	current_philo->thinking = false;
	ft_usleep(data->info->eat_time, data);
	pthread_mutex_lock(&data->mutex_time);
	current_philo->last_meal = get_current_time();
	pthread_mutex_unlock(&data->mutex_time);
	pthread_mutex_lock(&data->mutex_check);
	current_philo->nbr_eat += 1;
	pthread_mutex_unlock(&data->mutex_check);
	let_fork_r(current_philo);
	let_fork_l(current_philo);
	sleeping(data, current_philo);
}

static void	routine(t_data *data, t_philos *current_philo)
{
	pthread_mutex_lock(&current_philo->mutex_fork_r);
	if (current_philo->fork_r && current_philo->nbr_fork < 2)
	{
		pthread_mutex_unlock(&current_philo->mutex_fork_r);
		taking_fork_r(data, current_philo);
		pthread_mutex_lock(&current_philo->mutex_fork_r);
	}
	pthread_mutex_unlock(&current_philo->mutex_fork_r);
	pthread_mutex_lock(current_philo->mutex_fork_l);
	if (current_philo->fork_l && current_philo->nbr_fork < 2)
	{
		pthread_mutex_unlock(current_philo->mutex_fork_l);
		taking_fork_l(data, current_philo);
		pthread_mutex_lock(current_philo->mutex_fork_l);
	}
	pthread_mutex_unlock(current_philo->mutex_fork_l);
	if (current_philo->nbr_fork == 2)
		eating(data, current_philo);
	thinking(data, current_philo);
}

void	*thread_routine(void *d)
{
	t_data		*data;
	t_philos	*current_philo;

	current_philo = (t_philos *)d;
	data = current_philo->data;
	pthread_mutex_lock(&data->mutex_start);
	pthread_mutex_unlock(&data->mutex_start);
	if (!data)
		return (NULL);
	if (current_philo->index % 2 != 0)
		ft_usleep(10, data);
	while (1)
	{
		routine(data, current_philo);
		usleep(100);
		pthread_mutex_lock(&data->mutex_death);
		if (data->death)
		{
			pthread_mutex_unlock(&data->mutex_death);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_death);
	}
	return (NULL);
}
