/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:25:26 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/01 18:19:01 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_create(&sim->philosophers[i].thread, NULL, routine, &sim->philosophers[i]);
		i++;
	}
}

static void think(t_philosopher *philo);
static void take_forks(t_philosopher *philo);
static void eat(t_philosopher *philo);
static void release_forks(t_philosopher *philo);
static void rest(t_philosopher *philo);

void *routine (void *philosopher)
{
	t_philosopher	*philo;
	philo = (t_philosopher *)philosopher;
	while (1)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		rest(philo);
	}
	return (NULL);
}

static void think(t_philosopher *philo)
{
	printf("%ld: %d is thinking\n", get_time_in_ms(), philo->id);
}

static void take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->id]);
	printf("%ld: %d has taken a fork\n", get_time_in_ms(), philo->id);
	pthread_mutex_lock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
	printf("%ld: %d has taken a fork\n", get_time_in_ms(), philo->id);	
}

static void eat(t_philosopher *philo)
{
	printf("%ld: %d is eating\n", get_time_in_ms(), philo->id);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	usleep(philo->sim->time_to_eat * 1000);
}

static void release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
}

static void rest(t_philosopher *philo)
{
	printf("%ld: %d is sleeping\n", get_time_in_ms(), philo->id);
	usleep(philo->sim->time_to_sleep * 1000);
}