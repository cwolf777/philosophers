/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:14:12 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/24 15:35:23 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld %d is eating\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	smart_sleep(philo->sim->time_to_eat);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	if (philo->sim->num_philosophers != 1)
		pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1)
			% philo->sim->num_philosophers]);
	philo->has_both_forks = 0;
}

void	rest(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld %d is sleeping\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
	smart_sleep(philo->sim->time_to_sleep);
}
