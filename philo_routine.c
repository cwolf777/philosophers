/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:25:26 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/24 15:59:49 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	if (philo->sim->num_philosophers == 1)
	{
		one_philo_case(philo);
		return (NULL);
	}
	else
	{
		if (philo->id % 2 != 0)
			usleep(100);
		while (!check_death_flag(philo))
		{
			take_forks(philo);
			eat(philo);
			release_forks(philo);
			if (check_full_flag(philo))
				break ;
			rest(philo);
			think(philo);
		}
		return (NULL);
	}
}

void	think(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld %d is thinking\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

void	take_forks(t_philosopher *philo)
{
	int	first;
	int	second;

	first = philo->id;
	second = (philo->id + 1) % philo->sim->num_philosophers;
	if (first > second)
		swap_inits(&first, &second);
	if (philo->id % 2 != 0)
	{
		lock_first_fork(philo, first);
		lock_second_fork(philo, second);
	}
	else
	{
		lock_second_fork(philo, second);
		lock_first_fork(philo, first);
	}
}

void	lock_first_fork(t_philosopher *philo, int index)
{
	pthread_mutex_lock(&philo->sim->forks[index]);
	pthread_mutex_lock(&philo->sim->print_lock);
	if (!check_death_flag(philo))
		printf("%ld %d has taken a fork\n",
			get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

void	lock_second_fork(t_philosopher *philo, int index)
{
	pthread_mutex_lock(&philo->sim->forks[index]);
	pthread_mutex_lock(&philo->sim->print_lock);
	if (!check_death_flag(philo))
		printf("%ld %d has taken a fork\n",
			get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
}
