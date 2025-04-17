/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:53:20 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/17 14:57:02 by cwolf            ###   ########.fr       */
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
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); //Millisekunden
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

int check_death_flag(t_philosopher *philo)
{
	int	dead;
	pthread_mutex_lock(&philo->sim->death_lock);
	dead = philo->sim->sb_died;
	pthread_mutex_unlock(&philo->sim->death_lock);
	return	(dead);
}
int check_full_flag(t_philosopher *philo)
{
	int	finished;
	pthread_mutex_lock(&philo->is_full_lock);
	finished = philo->is_full;
	pthread_mutex_unlock(&philo->is_full_lock);
	return(finished);
}

void smart_sleep(t_philosopher *philo, long duration)
{
	long	start;
	long	left;

	start = get_time_in_ms();
	while(get_time_in_ms() - start < duration)
	{
		if (check_death_flag(philo))
			break ;
		left = duration - (get_time_in_ms() - start);
		if (left > 1000)
			usleep(left / 2 * 1000);
		else
		{
			while (get_time_in_ms() - start < duration)
				;
		}
	}
}

void one_philo_case(t_philosopher *philo)
{
	t_simulation *sim;
	int	duration;
	
	sim = philo->sim;
	duration = sim->time_to_die + 100;
	smart_sleep(philo, duration);
	// pthread_mutex_unlock(&philo->sim->forks[philo->id]);
	return ;
}

void cleanup(t_simulation *sim)
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