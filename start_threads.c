/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:10:11 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/18 14:22:23 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads(t_simulation *sim);
static int	create_waiter_thread(t_simulation *sim);
static void	join_all_threads(t_simulation *sim);

void	start_threads(t_simulation *sim)
{
	if (!create_philo_threads(sim))
		return ;
	if (!create_waiter_thread(sim))
		return ;
	join_all_threads(sim);
	cleanup(sim);
}

static int	create_philo_threads(t_simulation *sim)
{
	int	i;
	int	res;

	i = 0;
	while (i < sim->num_philosophers)
	{
		res = pthread_create(&sim->philosophers[i].thread,
				NULL, routine, &sim->philosophers[i]);
		if (res != 0)
		{
			printf("Failed creating thread!\n");
			cleanup(sim);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	create_waiter_thread(t_simulation *sim)
{
	int	res;

	res = pthread_create(&sim->waiter->thread, NULL, waiter_routine, sim);
	if (res != 0)
	{
		printf("Failed creating waiter thread!\n");
		cleanup(sim);
		return (0);
	}
	return (1);
}

static void	join_all_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philosophers)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(sim->waiter->thread, NULL);
}
