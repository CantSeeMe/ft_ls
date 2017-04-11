/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 19:56:36 by jye               #+#    #+#             */
/*   Updated: 2017/04/11 01:25:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct	s_lst
{
	struct	s_lst	*next;
	struct	s_lst	*prev;
	void			*data;
}				t_lst;

t_lst	*init_lst__(void *data)
{
	t_lst	*new;

	if ((new = (t_lst *)malloc(sizeof(t_lst))) == NULL)
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	push_lst__(t_lst **node, void *data)
{
	t_lst	*high_node;
	t_lst	*new_node;
	t_lst	*cur_node;

	if ((new_node = init_lst__(data)) == NULL)
		exit(1);
	cur_node = *node;
	if (cur_node)
	{
		high_node = cur_node->prev;
		cur_node->prev = new_node;
	}
	else
		high_node = NULL;
	new_node->next = cur_node;
	new_node->prev = high_node;
	*node = new_node;
}

void	pop_lst__(t_lst **node, void (*del)())
{
	t_lst	*high_node;
	t_lst	*pop_node;
	t_lst	*low_node;

	pop_node = *node;
	*node = pop_node->next;
	high_node = pop_node->prev;
	low_node = pop_node->next;
	if (high_node)
		high_node->next = low_node;
	if (low_node)
		low_node->prev = high_node;
	if (del)
		del(pop_node->data);
	free(pop_node);
}

void	append_lst__(t_lst *node, void *data)
{
	t_lst	*new_node;
	t_lst	*low_node;

	if ((new_node = init_lst__(data)) == NULL)
		exit(1);
	low_node = node->next;
	if (low_node)
		low_node->prev = new_node;
	node->next = new_node;
	new_node->next = low_node;
	new_node->prev = node;
}
