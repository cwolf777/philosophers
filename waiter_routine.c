/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:07:34 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/18 15:27:39 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_simulation *sim, t_philosopher *philo);
static void	check_philo_meals(t_simulation *sim,
				t_philosopher *philo, int *finished);
static int	all_philos_full(t_simulation *sim, int finished);

void	*waiter_routine(void *simulation)
{
	t_philosopher	*philo;
	t_simulation	*sim;
	int				i;
	int				finished;

	sim = (t_simulation *)simulation;
	finished = 0;
	while (1)
	{
		i = 0;
		while (i < sim->num_philosophers)
		{
			philo = &sim->philosophers[i];
			if (check_philo_death(sim, philo))
				return (NULL);
			check_philo_meals(sim, philo, &finished);
			i++;
		}
		if (all_philos_full(sim, finished))
			return (NULL);
		usleep(500);
	}
}

static int	check_philo_death(t_simulation *sim, t_philosopher *philo)
{
	long	now;

	pthread_mutex_lock(&philo->meal_lock);
	now = get_time_in_ms();
	if (now - philo->last_meal_time > sim->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_lock(&sim->print_lock);
		printf("%ld: Philosopher %d just died\n",
			get_time_stamp(philo), philo->id + 1);
		pthread_mutex_unlock(&sim->print_lock);
		pthread_mutex_lock(&sim->death_lock);
		sim->sb_died = 1;
		pthread_mutex_unlock(&sim->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static void	check_philo_meals(t_simulation *sim,
				t_philosopher *philo, int *finished)
{
	if (sim->must_eat != INT_MIN
		&& philo->meals_eaten == sim->must_eat && philo->is_full == 0)
	{
		(*finished)++;
		pthread_mutex_lock(&philo->is_full_lock);
		philo->is_full = 1;
		pthread_mutex_unlock(&philo->is_full_lock);
		pthread_mutex_lock(&sim->print_lock);
		printf("%ld: Philosopher %d has eaten enough!\n",
			get_time_stamp(philo), philo->id + 1);
		pthread_mutex_unlock(&sim->print_lock);
	}
}

static int	all_philos_full(t_simulation *sim, int finished)
{
	if (finished == sim->num_philosophers)
	{
		pthread_mutex_lock(&sim->print_lock);
		printf("All Philosophers have eaten enough!\n");
		pthread_mutex_unlock(&sim->print_lock);
		sim->all_full = 1;
		return (1);
	}
	return (0);
}
