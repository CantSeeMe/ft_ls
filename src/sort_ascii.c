/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:22:58 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:54:53 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		merge_p2(t_lst *sort, t_lst *b)
{
	t_file	*fa;
	t_file	*fb;

	while (b)
	{
		fa = (t_file *)sort->data;
		fb = (t_file *)b->data;
		if (ft_strcmp(fa->name, fb->name) <= 0)
		{
			if (sort->next == NULL)
			{
				append_lst__(sort, fb);
				pop_lst__(&b, NULL);
			}
			sort = sort->next;
		}
		else
		{
			push_lst__(&sort, fb);
			pop_lst__(&b, NULL);
			sort = sort->next;
		}
	}
}

static t_lst	*merge(t_lst *a, t_lst *b)
{
	t_file	*fa;
	t_file	*fb;

	if (b == NULL)
		return (a);
	fa = (t_file *)a->data;
	fb = (t_file *)b->data;
	if (ft_strcmp(fa->name, fb->name) >= 0)
	{
		push_lst__(&a, fb);
		pop_lst__(&b, NULL);
	}
	merge_p2(a, b);
	return (a);
}

t_lst			*sort_ascii(t_lst **stack, size_t slen)
{
	t_lst	*a;
	t_lst	*b;

	a = NULL;
	b = NULL;
	if (slen < 3)
	{
		push_lst__(&a, (*stack)->data);
		pop_lst__(stack, NULL);
		if (slen == 1)
			return (a);
		push_lst__(&b, (*stack)->data);
		pop_lst__(stack, NULL);
		return (merge(a, b));
	}
	a = sort_ascii(stack, slen % 2 ? (slen / 2) + 1 : slen / 2);
	b = sort_ascii(stack, slen / 2);
	return (merge(a, b));
}
