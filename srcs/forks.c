/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:03:18 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/21 07:08:19 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_fork_r(t_data *data, t_philos *current_philo)
{
	pthread_mutex_lock(&current_philo->mutex_fork_r);
	current_philo->fork_r = false;
	current_philo->next->fork_l = false;
	current_philo->nbr_fork += 1;
	print_msg("has taken a fork", data, current_philo, false);
	pthread_mutex_unlock(&current_philo->mutex_fork_r);
}

void	let_fork_r(t_philos *current_philo)
{
	pthread_mutex_lock(&current_philo->mutex_fork_r);
	current_philo->fork_r = true;
	current_philo->next->fork_l = true;
	current_philo->nbr_fork -= 1;
	pthread_mutex_unlock(&current_philo->mutex_fork_r);
}

void	taking_fork_l(t_data *data, t_philos *current_philo)
{
	pthread_mutex_lock(current_philo->mutex_fork_l);
	current_philo->fork_l = false;
	current_philo->prev->fork_r = false;
	current_philo->nbr_fork += 1;
	print_msg("has taken a fork", data, current_philo, false);
	pthread_mutex_unlock(current_philo->mutex_fork_l);
}

void	let_fork_l(t_philos *current_philo)
{
	pthread_mutex_lock(current_philo->mutex_fork_l);
	current_philo->fork_l = true;
	current_philo->prev->fork_r = true;
	current_philo->nbr_fork -= 1;
	pthread_mutex_unlock(current_philo->mutex_fork_l);
}
