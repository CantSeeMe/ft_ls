/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 01:14:51 by root              #+#    #+#             */
/*   Updated: 2017/04/11 03:35:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	swap(void *a, void *b)
{
	*(unsigned long *)a = *(unsigned long *)a ^ *(unsigned long *)b;
	*(unsigned long *)b = *(unsigned long *)b ^ *(unsigned long *)a;
	*(unsigned long *)a = *(unsigned long *)a ^ *(unsigned long *)b;
}

typedef struct	s_lst
{
	struct	s_lst	*next;
	struct	s_lst	*prev;
	void			*data;
}				t_lst;

t_lst	*init_lst__(void *data);
void	push_lst__(t_lst **node, void *data);
void	pop_lst__(t_lst **node, void (*del)());
void	append_lst__(t_lst *node, void *data);

t_lst	*merge_right()
{}

t_lst	*merge_left()
{}

t_lst	*merge(t_lst **stack, size_t stack_size)
{
	t_lst	*left;
	t_lst	*right;
	t_lst	*merged;

	if (stack_size < 3)
	{
		return ();
	}
	left = merge(stack, stack_size / 2);
	right = merge(stack, stack_size / 2);
	merged = stack_merge(left, right);
	return (merged);
}

int		main(int ac, char **av)
{
	t_lst	*lst;
	t_lst	*tmp;
	size_t	array_size = ac - 1;

	lst = init_lst__(NULL);
	tmp = lst;
	for (int i = 1; i < ac; i++)
	{
		append_lst__(tmp, (void *)(long)atoi(av[i]));
		tmp = tmp->next;
	}
	pop_lst__(&lst, NULL);
}
