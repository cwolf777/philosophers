/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:25:26 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/09 16:52:39 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_threads(t_simulation *sim)
{
	int	i;
	int res;

	i = 0;
	while (i < sim->num_philosophers)
	{
		res = pthread_create(&sim->philosophers[i].thread, NULL, routine, &sim->philosophers[i]);
		if (res != 0)
		{
			printf("Failed creating thread!\n");
			exit(1); // EXIT FUNKLTION NÖTIG	
		}
		i++;
	}
	i = 0;
	while(i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	//pthread destroy gegen leaks
}

static void think(t_philosopher *philo);
static void take_forks(t_philosopher *philo);
static void eat(t_philosopher *philo);
static void release_forks(t_philosopher *philo);
static void rest(t_philosopher *philo);
static int check_on_philo(t_philosopher *philo);
static int	can_philo_eat(t_philosopher *philo);
static int is_near_death(t_philosopher *philo);

void *routine (void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (check_on_philo(philo) != 1)
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		rest(philo);

	}
	pthread_exit(NULL);
	return (NULL);
}

static int check_on_philo(t_philosopher *philo)
{
	long	not_eaten;
	long	now;
	long	time_stamp;

	now = get_time_in_ms();
	time_stamp = get_time_stamp(philo);
	not_eaten = now - philo->last_meal_time;
	if (philo->meals_eaten >= philo->sim->must_eat && philo->sim->must_eat != INT_MIN)
	{
		printf("%ld: Philosopher %d has eaten enough\n", time_stamp, philo->id);
		return (1);
	}
	else if (not_eaten > philo->sim->time_to_die)
	{
		printf("%ld: Philosopher %d died\n", time_stamp, philo->id);
		return (1);
	}
	else
		return (0);
	
}

static int	can_philo_eat(t_philosopher *philo)
{	
	int	left_id;
	int	right_id;
	t_philosopher	*right_philo;
	t_philosopher	*left_philo;
	
	if (philo->sim->num_philosophers == 1)
		return (1);
	pthread_mutex_lock(&philo->sim->monitor_lock);
	left_id = (philo->id - 1 + philo->sim->num_philosophers) % philo->sim->num_philosophers;
	right_id = (philo->id + 1) % philo->sim->num_philosophers;
	left_philo = &philo->sim->philosophers[left_id];
	right_philo = &philo->sim->philosophers[right_id];

	if (is_near_death(left_philo) || is_near_death(right_philo))
	{
		pthread_mutex_unlock(&philo->sim->monitor_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->sim->monitor_lock);
	return (1);	
	
}
static int is_near_death(t_philosopher *philo)
{
	long	now;
	long	not_eaten;

	now = get_time_in_ms();
	not_eaten = now - philo->last_meal_time;
	if (philo->sim->time_to_eat * 2 <= philo->sim->time_to_die - not_eaten)
		return(1);
	return (0);
}

static void think(t_philosopher *philo)
{
	printf("%ld: %d is thinking\n", get_time_stamp(philo), philo->id);
}

static void take_forks(t_philosopher *philo)
{
	if (philo->id % 2 != 0)
		usleep(200);
	while (!can_philo_eat(philo))
		usleep(200);
	pthread_mutex_lock(&philo->sim->forks[philo->id]);
	printf("%ld: %d has taken a fork\n", get_time_stamp(philo), philo->id);
	if (philo->sim->num_philosophers == 1)
		return ;
	pthread_mutex_lock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
	printf("%ld: %d has taken a fork\n", get_time_stamp(philo), philo->id);
	philo->has_both_forks = 1;
	return ;
}

static void eat(t_philosopher *philo)
{
	if (philo->has_both_forks == 1)
	{
		printf("%ld: %d is eating\n", get_time_stamp(philo), philo->id);
		philo->last_meal_time = get_time_in_ms();
		philo->meals_eaten++;
		usleep(philo->sim->time_to_eat * 1000);
	}
}

static void release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	if (philo->sim->num_philosophers != 1)
		pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
	philo->has_both_forks = 0;
}

static void rest(t_philosopher *philo)
{
	printf("%ld: %d is sleeping\n", get_time_stamp(philo), philo->id);
	usleep(philo->sim->time_to_sleep * 1000);
}