/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:19:46 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/09 14:51:23 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat]\n"));
	t_simulation *sim;

	sim = init_simulation(argv);
	if (sim == NULL)
	{
		printf("Failure while initiliazing\n");
		return (EXIT_FAILURE);
	}
    // print_simulation_info(sim);
	start_threads(sim);
	return (0);
}
