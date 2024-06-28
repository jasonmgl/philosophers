/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:05:55 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/22 07:19:23 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_all_ate(t_data *data)
{
	size_t		i;
	size_t		count;
	t_philos	*ptr;

	i = 0;
	count = 0;
	if (!data)
		return (0);
	ptr = data->lst;
	while (i < data->info->nbr_philo)
	{
		pthread_mutex_lock(&data->mutex_check);
		if (ptr->nbr_eat >= data->info->nbr_eat)
			count++;
		pthread_mutex_unlock(&data->mutex_check);
		ptr = ptr->next;
		i++;
	}
	if (count == data->info->nbr_philo)
		return (1);
	return (0);
}

void	if_philo_died(t_data *data)
{
	size_t		i;
	t_philos	*ptr;

	i = 0;
	if (!data)
		return ;
	ptr = data->lst;
	while (i++ < data->info->nbr_philo)
	{
		pthread_mutex_lock(&data->mutex_time);
		if (ptr->last_meal == 0)
			ptr->last_meal = get_current_time();
		pthread_mutex_unlock(&data->mutex_time);
		pthread_mutex_lock(&data->mutex_time);
		if ((data->current_time - ptr->last_meal) >= data->info->die_time)
		{
			pthread_mutex_unlock(&data->mutex_time);
			print_msg("died", data, ptr, true);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_time);
		ptr = ptr->next;
	}
	return ;
}

int	check_digit(char **argv)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	if (!argv || !*argv)
		return (0);
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	check_args(t_info *info)
{
	if (!info)
		return (0);
	if (info->die_time < 60)
		return (0);
	if (info->eat_time < 60)
		return (0);
	if (info->sleep_time < 60)
		return (0);
	if (info->nbr_philo == 0 || info->nbr_philo > 200)
		return (0);
	if (info->nbr_eat == 0)
		return (0);
	return (1);
}
