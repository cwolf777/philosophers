/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:12:20 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/01 16:15:55 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_simulation_info(t_simulation *sim) 
{
    printf("📌 Simulation gestartet mit %d Philosophen\n", sim->num_philosophers);
    printf("   Zeit bis zum Tod: %d ms\n", sim->time_to_die);
    printf("   Zeit zum Essen: %d ms\n", sim->time_to_eat);
    printf("   Zeit zum Schlafen: %d ms\n", sim->time_to_sleep);
    printf("   Mindest-Mahlzeiten: %d\n", sim->must_eat);
    printf("   Startzeit: %ld ms\n", sim->start_time);
    
    for (int i = 0; i < sim->num_philosophers; i++) {
        printf("🔹 Philosoph %d | Letzte Mahlzeit: %ld | Mahlzeiten gegessen: %d\n",
               sim->philosophers[i].id, sim->philosophers[i].last_meal_time, sim->philosophers[i].meals_eaten);
    }
}