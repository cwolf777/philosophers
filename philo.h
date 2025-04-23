/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:20:04 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/23 11:20:54 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_waiter
{
	pthread_t			thread;
	struct s_simulation	*sim;
}			t_waiter;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		is_full_lock;
	long				last_meal_time;
	int					meals_eaten;
	int					has_both_forks;
	int					is_full;
	struct s_simulation	*sim;
}			t_philosopher;

typedef struct s_simulation
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				sb_died;
	int				all_full;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	t_philosopher	*philosophers;
	t_waiter		*waiter;
	long			start_time;
}			t_simulation;

// GARBAGE COLLECTOR

typedef struct s_gc_node
{
	void				*ptr;
	struct s_gc_node	*next;
}						t_gc_node;

typedef struct s_gc_manager
{
	t_gc_node			*head;
}						t_gc_manager;

void			*gc_alloc(int size);
void			gc_free_all(void);
t_gc_manager	*get_gc_instance(void);

//Philo
long			ft_atolo(const char *str);
t_simulation	*init_simulation(char **argv);
long			get_time_in_ms(void);
long			get_time_stamp(t_philosopher *philo);
void			start_threads(t_simulation *sim);
void			*routine(void *philosopher);
void			*waiter_routine(void *simulation);
int				input_time_check(t_simulation *sim, char **argv);
int				check_death_flag(t_philosopher *philo);
void			smart_sleep(t_philosopher *philo, long duration);
int				check_full_flag(t_philosopher *philo);
void			one_philo_case(t_philosopher *philo);
void			cleanup(t_simulation *sim);
void			swap_inits(int *a, int *b);
void			think(t_philosopher *philo);
void			take_forks(t_philosopher *philo);
void			lock_first_fork(t_philosopher *philo, int index);
void			lock_second_fork(t_philosopher *philo, int index);
void			eat(t_philosopher *philo);
void			release_forks(t_philosopher *philo);
void			rest(t_philosopher *philo);

#endif