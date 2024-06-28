/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:19:55 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/22 07:36:54 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_time(t_data *data)
{
	if (if_all_ate(data) && data->info->nbr_eat != -1)
	{
		pthread_mutex_lock(&data->mutex_death);
		data->death = true;
		pthread_mutex_unlock(&data->mutex_death);
	}
	pthread_mutex_lock(&data->mutex_time);
	data->current_time = get_current_time();
	pthread_mutex_unlock(&data->mutex_time);
	if_philo_died(data);
}

static void	main_routine(t_data *data)
{
	size_t		i;
	t_philos	*ptr;

	i = 0;
	if (!data)
		return ;
	ptr = data->lst;
	pthread_mutex_lock(&data->mutex_death);
	while (!data->death)
	{
		pthread_mutex_unlock(&data->mutex_death);
		update_time(data);
		pthread_mutex_lock(&data->mutex_death);
	}
	pthread_mutex_unlock(&data->mutex_death);
	while (i < data->info->nbr_philo)
	{
		pthread_join(ptr->tid, NULL);
		ptr = ptr->next;
		i++;
	}
}

static int	philo(t_info *info)
{
	t_data	*data;

	if (!info)
		return (0);
	data = init_data(info);
	if (!data)
		return (0);
	data->f = &thread_routine;
	init_mutex(data);
	pthread_mutex_lock(&data->mutex_start);
	if (!create_threads(data))
		return (ft_exit("pthread_create\n", 2, data->lst, data));
	pthread_mutex_lock(&data->mutex_time);
	data->start_time = get_current_time();
	data->current_time = get_current_time();
	pthread_mutex_unlock(&data->mutex_time);
	pthread_mutex_unlock(&data->mutex_start);
	main_routine(data);
	return (ft_exit(NULL, 1, data->lst, data));
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		if (!check_digit(argv))
			return (error_msg(BAD_FORMAT));
		info = init_info(argc, argv);
		if (!check_args(&info))
			return (error_msg(BAD_LIMITS));
		if (!philo(&info))
			return (1);
	}
	else
		return (error_msg(BAD_ARGS));
	return (0);
}
