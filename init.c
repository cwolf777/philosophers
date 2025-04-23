/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:27:12 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/23 14:03:22 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_simulation	*init_sim_memory(char **argv);
static int			init_sim_flags(t_simulation *sim, char **argv);
static void			init_sim_locks(t_simulation *sim);
static void			init_philo_flags(t_simulation *sim);

t_simulation	*init_simulation(char **argv)
{
	t_simulation	*sim;

	sim = init_sim_memory(argv);
	if (!sim)
	{
		gc_free_all();
		return (NULL);
	}
	init_sim_locks(sim);
	init_philo_flags(sim);
	return (sim);
}

static t_simulation	*init_sim_memory(char **argv)
{
	t_simulation	*sim;

	sim = gc_alloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	if (init_sim_flags(sim, argv) == 0)
		return (NULL);
	sim->waiter = gc_alloc(sizeof(t_waiter));
	if (!sim->waiter)
		return (NULL);
	sim->waiter->sim = sim;
	sim->philosophers = gc_alloc(sizeof(t_philosopher) * sim->num_philosophers);
	if (!sim->philosophers)
		return (NULL);
	sim->forks = gc_alloc(sizeof(pthread_mutex_t) * sim->num_philosophers);
	if (!sim->forks)
		return (NULL);
	return (sim);
}

static int	init_sim_flags(t_simulation *sim, char **argv)
{
	sim->num_philosophers = ft_atolo(argv[1]);
	sim->time_to_die = ft_atolo(argv[2]);
	sim->time_to_eat = ft_atolo(argv[3]);
	sim->time_to_sleep = ft_atolo(argv[4]);
	if (argv[5] != NULL)
		sim->must_eat = ft_atolo(argv[5]);
	else
		sim->must_eat = INT_MIN;
	if (input_time_check(sim, argv) == 0)
		return (0);
	sim->start_time = get_time_in_ms();
	sim->sb_died = 0;
	sim->all_full = 0;
	return (1);
}

static void	init_sim_locks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		pthread_mutex_init(&sim->philosophers[i].meal_lock, NULL);
		pthread_mutex_init(&sim->philosophers[i].is_full_lock, NULL);
		i++;
	}
	pthread_mutex_init(&sim->print_lock, NULL);
	pthread_mutex_init(&sim->death_lock, NULL);
	return ;
}

static void	init_philo_flags(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].last_meal_time = sim->start_time;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].has_both_forks = 0;
		sim->philosophers[i].is_full = 0;
		i++;
	}
}
