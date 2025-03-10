/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:29:33 by aroux             #+#    #+#             */
/*   Updated: 2025/03/10 18:53:58 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* customed malloc function that fills the gc list with a new element (ptr) */
void	*gc_malloc(t_data *data, size_t size)
{
	void	*ptr;
	t_gc	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->next = data->gc_list;
	data->gc_list = new_node;
	return (ptr);
}

/* frees all elements in the garbage collector */
void	gc_free_all(t_data *data)
{
	t_gc	*curr;

	while (data->gc_list)
	{
		curr = data->gc_list;
		data->gc_list = data->gc_list->next;
		free(curr->ptr);
		free(curr);
	}
}

/* custom free function that removes one element from the gc_list */
void	gc_free(t_data *data, void *ptr)
{
	t_gc	*prev;
	t_gc	*curr;

	prev = NULL;
	curr = data->gc_list;
	while (curr)
	{
		if (curr->ptr == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				data->gc_list = curr->next;
			free(curr->ptr);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

