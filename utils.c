/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:53:20 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/09 14:49:20 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atolo(const char *str)
{
	long	number;
	int		minus_check;
	int		i;

	minus_check = 1;
	i = 0;
	number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus_check = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		return (INT_MIN);
	}
	return (number * minus_check);
}

long get_time_in_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long get_time_stamp(t_philosopher *philo)
{
	long	now;
	long	time_stamp;
	
	now = get_time_in_ms();
	time_stamp = now - philo->sim->start_time;

	return(time_stamp);
}

int input_time_check(t_simulation *sim, char **argv)
{
	if (argv[5])
	{
		if (sim->must_eat <= 0)
			return (0);
	}
	if (sim->time_to_die < 60 || sim->time_to_eat < 60 || sim->time_to_sleep < 60 || //wenn Buchstabe (INT MIN) oder weniger ls 60 ms
		sim->num_philosophers <= 0)
		return (0);
	else if (sim->time_to_die > INT_MAX || sim->time_to_eat > INT_MAX || sim->time_to_sleep > INT_MAX || //wenn groeser als INT
		sim->num_philosophers > INT_MAX || sim->must_eat > INT_MAX)
		return (0);
	else
		return (1);
}