/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:25:26 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/17 10:34:19 by cwolf            ###   ########.fr       */
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
	res = pthread_create(&sim->waiter->thread, NULL, waiter_routine, sim);
	if (res != 0)
	{
		printf("Failed creating waiter thread!\n");
		exit(1); // EXIT FUNKLTION NÖTIG	
	}
	while(i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(sim->waiter->thread, NULL);
	//pthread destroy gegen leaks
	// Alle Philosophen-Threads beenden (z.B. durch shared flags oder pthread_cancel)
	// Speicher freigeben
	// Programm sauber beenden
}

static void think(t_philosopher *philo);
static void take_forks(t_philosopher *philo);
static void eat(t_philosopher *philo);
static void release_forks(t_philosopher *philo);
static void rest(t_philosopher *philo);
// static void smart_sleep(t_philosopher *philo);
// static int check_on_philo(t_philosopher *philo);
// static int	can_philo_eat(t_philosopher *philo);


void *waiter_routine(void *simulation)
{
	int			i;
	int			finished;
	long		now;
	t_philosopher	*philo;
	t_simulation	*sim;

	sim = (t_simulation *)simulation;
	finished = 0;

	while (1)
	{
		i = 0;
		while (i < sim->num_philosophers)
		{
			// update_prios(sim);
			philo = &sim->philosophers[i];
			pthread_mutex_lock(&philo->meal_lock);
			now = get_time_in_ms();
			if (now - philo->last_meal_time > sim->time_to_die ) //!!!! && philo->sim->sb_died == 0
			{
				pthread_mutex_unlock(&philo->meal_lock);
				pthread_mutex_lock(&sim->print_lock);
				printf("%ld: Philosopher %d just died\n", get_time_stamp(philo), philo->id + 1);
				pthread_mutex_unlock(&sim->print_lock);
				pthread_mutex_lock(&sim->death_lock);
				sim->sb_died = 1;
				pthread_mutex_unlock(&sim->death_lock);
				return (NULL);
			}
			if (sim->must_eat != INT_MIN && philo->meals_eaten == sim->must_eat && philo->is_full == 0)
			{
				finished++;
				philo->is_full = 1;
				pthread_mutex_lock(&sim->print_lock);
				printf("%ld: Philosopher %d has eaten enough!\n", get_time_stamp(philo), philo->id + 1);
				pthread_mutex_unlock(&sim->print_lock);
			}
			pthread_mutex_unlock(&philo->meal_lock);
			i++;
		}
		if (finished == sim->num_philosophers )
		{
			pthread_mutex_lock(&sim->print_lock);
			printf("All Philosophers have eaten enough!\n");
			pthread_mutex_unlock(&sim->print_lock);
			sim->all_full = 1;
			return (NULL);
		}
		usleep(500);
	}	
}

void *routine (void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (!check_death_flag(philo))
	{
		// if (prio_check_neighbor(philo) && philo->prio != 1)
		// 	usleep(500);
		think(philo);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		if (check_full_flag(philo))
			break ;
		rest(philo);
	}
	// pthread_exit(NULL);
	return (NULL);
}

static void think(t_philosopher *philo)
{
	// if (check_death_flag(philo))
	// 	return ;
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld: %d is thinking\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
}

static void take_forks(t_philosopher *philo)
{
	// int	time_stamp;

	// if (check_death_flag(philo))
	// 	return ;
	if (philo->id % 2 != 0)
	{
		usleep(100);
	}
	pthread_mutex_lock(&philo->sim->forks[philo->id]);
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld: %d has taken a fork\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
	if (philo->sim->num_philosophers == 1)
	{
		one_philo_case(philo);
		return ;
	}
	pthread_mutex_lock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld: %d has taken a fork\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
	philo->has_both_forks = 1;

	return ;
}

static void eat(t_philosopher *philo)
{
	// if (check_death_flag(philo))
	// 	return ;
	
	if (philo->has_both_forks == 1)
	{
		pthread_mutex_lock(&philo->meal_lock);
		pthread_mutex_lock(&philo->sim->print_lock);
		if (check_death_flag(philo) == 0)
			printf("%ld: %d is eating\n", get_time_stamp(philo), philo->id + 1);
		pthread_mutex_unlock(&philo->sim->print_lock);
		philo->last_meal_time = get_time_in_ms();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_lock);
		smart_sleep(philo, philo->sim->time_to_eat);
	}
}

static void release_forks(t_philosopher *philo)
{
	// if (check_death_flag(philo))
	// 	return ;
	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	if (philo->sim->num_philosophers != 1)
		pthread_mutex_unlock(&philo->sim->forks[(philo->id + 1) % philo->sim->num_philosophers]);
	philo->has_both_forks = 0;
}

static void rest(t_philosopher *philo)
{
	// long	now;
	// if (check_death_flag(philo))
	// 	return ;

	// now = get_time_in_ms();
	// if (now - philo->last_meal_time + philo->sim->time_to_sleep > philo->sim->time_to_die)
	// {
	// 	smart_sleep(philo);
	// }

	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld: %d is sleeping\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
	smart_sleep(philo, philo->sim->time_to_sleep);
}

