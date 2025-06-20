/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:19:46 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/18 15:25:20 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	*sim;

	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments!\n"));
	sim = init_simulation(argv);
	if (sim == NULL)
	{
		printf("Failure while initiliazing\n");
		return (EXIT_FAILURE);
	}
	start_threads(sim);
	return (0);
}
