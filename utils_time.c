/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:23:15 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/23 15:35:53 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_time_stamp(t_philosopher *philo)
{
	long	now;
	long	time_stamp;

	now = get_time_in_ms();
	time_stamp = now - philo->sim->start_time;
	return (time_stamp);
}

int	input_time_check(t_simulation *sim, char **argv)
{
	if (argv[5])
	{
		if (sim->must_eat <= 0)
			return (0);
	}
	if (sim->time_to_die < 60 || sim->time_to_eat < 60
		|| sim->time_to_sleep < 60 || sim->num_philosophers <= 0)
		return (0);
	else if (sim->time_to_die > INT_MAX || sim->time_to_eat > INT_MAX
		|| sim->time_to_sleep > INT_MAX
		|| sim->num_philosophers > INT_MAX || sim->must_eat > INT_MAX)
		return (0);
	else if (sim->num_philosophers > 200)
		return (0);
	else
		return (1);
}
