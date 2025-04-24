/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:53:20 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/24 15:39:20 by cwolf            ###   ########.fr       */
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

void	smart_sleep(long duration)
{
	long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < duration)
		usleep(500);
}

void	one_philo_case(t_philosopher *philo)
{
	t_simulation	*sim;
	int				duration;

	sim = philo->sim;
	duration = sim->time_to_die + 100;
	pthread_mutex_lock(&philo->sim->print_lock);
	if (check_death_flag(philo) == 0)
		printf("%ld: %d is thinking\n", get_time_stamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim->print_lock);
	lock_first_fork(philo, philo->id);
	smart_sleep(duration);
	pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	return ;
}

void	cleanup(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->death_lock);
	while (i < sim->num_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philosophers[i].meal_lock);
		pthread_mutex_destroy(&sim->philosophers[i].is_full_lock);
		i++;
	}
	gc_free_all();
	return ;
}

void	swap_inits(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
