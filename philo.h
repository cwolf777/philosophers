/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:20:04 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/16 09:45:30 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>


typedef struct s_waiter{
    pthread_t thread;
    struct s_simulation *sim;
}  t_waiter;

typedef struct s_philosopher {
    int id;
    pthread_t thread;
    pthread_mutex_t meal_lock;
    long last_meal_time;
    int meals_eaten;
    int has_both_forks;
    int is_full;
    struct s_simulation *sim;
} t_philosopher;

typedef struct s_simulation {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int sb_died;
    int all_full;
    pthread_mutex_t death_lock;
    pthread_mutex_t *forks; // mutex auf forks
    pthread_mutex_t print_lock; // mutex auf print ausgabe 
    t_philosopher *philosophers; // array von Philosophen 
    t_waiter *waiter; //pointer auf waiter? mit oder ohen stern
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
long	ft_atolo(const char *str);
t_simulation *init_simulation(char **argv);
long get_time_in_ms(void);
long get_time_stamp(t_philosopher *philo);
void print_simulation_info(t_simulation *sim);
void start_threads(t_simulation *sim);
void *routine (void *philosopher);
void *waiter_routine(void *simulation);
int input_time_check(t_simulation *sim, char **argv);
int check_death_flag(t_philosopher *philo);
// void	update_prios(t_simulation *sim);
// int prio_check_neighbor(t_philosopher *philo);
void smart_sleep(t_philosopher *philo, long duration);
int check_full_flag(t_philosopher *philo);
void one_philo_case(t_philosopher *philo);

#endif