/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:19:46 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/08 14:42:29 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat]\n"), 1;
	t_simulation *sim;

	sim = init_simulation(argc, argv);
    // print_simulation_info(sim);
	start_threads(sim);
	return (0);
}
