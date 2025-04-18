/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:23:45 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/18 15:26:56 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_philosopher *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->sim->death_lock);
	dead = philo->sim->sb_died;
	pthread_mutex_unlock(&philo->sim->death_lock);
	return (dead);
}

int	check_full_flag(t_philosopher *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->is_full_lock);
	finished = philo->is_full;
	pthread_mutex_unlock(&philo->is_full_lock);
	return (finished);
}
