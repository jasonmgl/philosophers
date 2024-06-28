/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:08:01 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/22 07:55:02 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_printf);
	pthread_mutex_destroy(&data->mutex_time);
	pthread_mutex_destroy(&data->mutex_start);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_check);
}

void	free_philos(t_philos **lst)
{
	t_philos	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = NULL;
	while ((*lst)->last == false)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		pthread_mutex_destroy(&tmp->mutex_fork_r);
		free(tmp);
	}
	tmp = *lst;
	pthread_mutex_destroy(&tmp->mutex_fork_r);
	free(tmp);
	tmp = NULL;
	lst = NULL;
}

int	error_msg(char *str)
{
	write(2, ERROR, 16);
	if (str)
		printf("%s\n", str);
	return (EXIT_FAILURE);
}

int	ft_exit(char *str, int fd, t_philos *lst, t_data *data)
{
	if (fd == 1 || fd == 2)
	{
		if (fd == 2)
			ft_putstr_fd("\e[31mError\n\e[0m", 2);
		if (str)
			ft_putstr_fd(str, fd);
		if (lst)
			free_philos(&lst);
		if (data)
		{
			pthread_mutex_lock(&data->mutex_death);
			data->death = true;
			pthread_mutex_unlock(&data->mutex_death);
			destroy_all_mutex(data);
			free(data);
			data = NULL;
		}
		if (fd == 1)
			return (1);
	}
	return (0);
}
