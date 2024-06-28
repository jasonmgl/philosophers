/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:09:30 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/21 07:08:19 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*init_philos(t_data *data)
{
	t_philos	*lst;
	t_philos	*ptr;
	t_philos	*last;
	size_t		i;

	if (!data)
		return (NULL);
	i = 0;
	lst = NULL;
	while (i < data->info->nbr_philo)
		if (ft_lstadd_back(&lst, ft_lstnew(i++, data)) == 0)
			return (free_philos(&lst), NULL);
	ptr = lst;
	while (ptr)
	{
		ptr->mutex_fork_l = &ptr->prev->mutex_fork_r;
		ptr = ptr->next;
	}
	last = ft_lstlast(lst);
	last->last = true;
	last->next = lst;
	lst->prev = last;
	lst->mutex_fork_l = &lst->prev->mutex_fork_r;
	return (lst);
}

int	create_threads(t_data *data)
{
	t_philos	*ptr;
	size_t		i;

	if (!data)
		return (0);
	ptr = data->lst;
	i = 0;
	while (i < data->info->nbr_philo)
	{
		if (pthread_create(&ptr->tid, NULL, data->f, ptr) != 0)
			return (0);
		ptr = ptr->next;
		i++;
	}
	return (1);
}

t_data	*init_data(t_info *info)
{
	t_data	*data;

	if (!info)
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data) * 1);
	if (!data)
		return (ft_exit("malloc()\n", 2, NULL, NULL), NULL);
	memset(data, 0, sizeof(t_data));
	data->death = false;
	data->info = info;
	data->current_time = get_current_time();
	data->lst = init_philos(data);
	if (!data->lst)
		return (ft_exit(NULL, 1, NULL, data), NULL);
	return (data);
}

void	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->mutex_time, NULL);
	pthread_mutex_init(&data->mutex_start, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_check, NULL);
}

t_info	init_info(int argc, char**argv)
{
	t_info	info;

	memset(&info, 0, sizeof(info));
	info.nbr_philo = ft_atoi(argv[1]);
	info.die_time = ft_atoi(argv[2]);
	info.eat_time = ft_atoi(argv[3]);
	info.sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info.nbr_eat = ft_atoi(argv[5]);
	else
		info.nbr_eat = -1;
	return (info);
}
