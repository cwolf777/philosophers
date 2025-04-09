/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:27:12 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/09 16:30:24 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simulation *init_simulation(char **argv)
{
	t_simulation *sim;
	int				i;

	i = 0;
	sim = gc_alloc(sizeof(t_simulation));

	sim->num_philosophers = ft_atolo(argv[1]);
	sim->time_to_die = ft_atolo(argv[2]);
	sim->time_to_eat = ft_atolo(argv[3]);
	sim->time_to_sleep = ft_atolo(argv[4]);
	if (argv[5] != NULL)
		sim->must_eat = ft_atolo(argv[5]);
	else
		sim->must_eat = INT_MIN;
	if (input_time_check(sim, argv) == 0)
		return (NULL);
	sim->start_time = get_time_in_ms();
	sim->forks = gc_alloc(sizeof(pthread_mutex_t) * sim->num_philosophers);
	while (i < sim->num_philosophers) 
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&sim->print_lock, NULL);
	sim->philosophers = gc_alloc(sizeof(t_philosopher) * sim->num_philosophers);
	i = 0;
	while (i < sim->num_philosophers)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].last_meal_time = sim->start_time;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].has_both_forks = 0; //0 = nein
		i++;
	}
	return (sim);
}
