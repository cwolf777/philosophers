/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:29:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/01 14:54:30 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gc_print_list(void)
{
	t_gc_manager	*gc;
	t_gc_node		*current;

	gc = get_gc_instance();
	current = gc->head;
	if (!current)
	{
		printf("Garbage Collector List is empty.\n");
		return ;
	}
	printf("Garbage Collector List:\n");
	while (current)
	{
		printf("Allocated memory at: %p\n", current->ptr);
		current = current->next;
	}
}

t_gc_manager	*get_gc_instance(void)
{
	static t_gc_manager	gc = {NULL};

	return (&gc);
}

void	*gc_alloc(int size)
{
	void			*ptr;
	t_gc_node		*node;
	t_gc_manager	*gc;

	gc = get_gc_instance();
	ptr = malloc(size);
	if (!ptr)
	{
		gc_free_all();
		exit(1);
		//panic("malloc failed"); //PANIC ERSTELLEN
	}
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		gc_free_all();
		exit(1);
		//panic("malloc failed");
	}
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	gc_free_all(void)
{
	t_gc_node		*node;
	t_gc_node		*next;
	t_gc_manager	*gc;

	gc = get_gc_instance();
	node = gc->head;
	while (node)
	{
		next = node->next;
		free(node->ptr);
		free(node);
		node = next;
	}
	gc->head = NULL;
}

void	gc_free_one(void *ptr)
{
	t_gc_manager	*gc;
	t_gc_node		*prev;
	t_gc_node		*curr;

	gc = get_gc_instance();
	prev = NULL;
	curr = gc->head;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				gc->head = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	printf("Warning: Trying to free ptr not in gc list\n");
}