/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:20:04 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/08 14:13:04 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    pthread_t thread;
    long last_meal_time;
    int meals_eaten;
    struct s_simulation *sim;
} t_philosopher;

typedef struct s_simulation {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    pthread_mutex_t *forks; // mutex auf forks
    pthread_mutex_t print_lock; // mutex auf print ausgabe 
    pthread_mutex_t monitor_lock; //mutex auf Kellner
    t_philosopher *philosophers; // array von Philosophen 
    long start_time; // Startzeitpunkt der Simulation
} t_simulation;

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

void					*gc_alloc(int size);
void					gc_free_all(void);
void					gc_free_one(void *ptr);
t_gc_manager			*get_gc_instance(void);
void					gc_print_list(void);

//Philo
int	ft_atoi(const char *str);
t_simulation *init_simulation(int argc, char **argv);
long get_time_in_ms(void);
void print_simulation_info(t_simulation *sim);
void start_threads(t_simulation *sim);
void *routine (void *philosopher);

#endif