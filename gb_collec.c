/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:29:57 by cwolf             #+#    #+#             */
/*   Updated: 2025/04/18 14:29:27 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (NULL);
	}
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		gc_free_all();
		return (NULL);
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
