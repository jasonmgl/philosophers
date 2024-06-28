/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:29:33 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/20 08:07:39 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*ft_lstnew(int index, t_data *data)
{
	t_philos	*philo;

	philo = (t_philos *)malloc(sizeof(t_philos) * 1);
	if (!philo)
		return (ft_exit("malloc()\n", 2, NULL, NULL), NULL);
	memset(philo, 0, sizeof(t_philos));
	philo->data = data;
	philo->index = index + 1;
	philo->fork_l = true;
	philo->fork_r = true;
	pthread_mutex_init(&philo->mutex_fork_r, NULL);
	return (philo);
}

int	ft_lstadd_back(t_philos **lst, t_philos *new)
{
	t_philos	*last;

	if (!new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		if (!*lst)
			return (0);
		return (1);
	}
	last = ft_lstlast(*lst);
	last->next = new;
	if (!last->next)
		return (0);
	new->prev = last;
	return (1);
}

t_philos	*ft_lstlast(t_philos *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
