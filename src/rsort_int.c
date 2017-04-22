/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsort_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 19:10:21 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:55:20 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static time_t	sort_time_then_ascii(t_file *a, t_file *b)
{
	if (a->time->tv_sec > b->time->tv_sec)
		return (-1);
	else if (a->time->tv_sec < b->time->tv_sec)
		return (1);
	else
		return (ft_strcmp(a->name, b->name));
}

static void		merge_p2(t_lst *sort, t_lst *b)
{
	t_file	*fb;
	t_file	*fa;

	while (b)
	{
		fa = (t_file *)sort->data;
		fb = (t_file *)b->data;
		if (sort_time_then_ascii(fa, fb) >= 0)
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
	if (sort_time_then_ascii(fa, fb) <= 0)
	{
		push_lst__(&a, fb);
		pop_lst__(&b, NULL);
	}
	merge_p2(a, b);
	return (a);
}

t_lst			*rsort_int(t_lst **stack, size_t slen)
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
	a = rsort_int(stack, slen % 2 ? (slen / 2) + 1 : slen / 2);
	b = rsort_int(stack, slen / 2);
	return (merge(a, b));
}
