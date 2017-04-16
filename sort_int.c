/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:46:47 by jye               #+#    #+#             */
/*   Updated: 2017/04/16 00:46:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static time_t	sort_time_then_ascii(t_file *a, t_file *b)
{
	if (a->time->tv_sec > b->time->tv_sec)
		return (-1);
	else if (a->time->tv_sec < b->time->tv_sec)
		return (1);
#ifdef __linux__
	if (a->time->tv_nsec > b->time->tv_nsec)
		return (-1);
	else if (a->time->tv_sec < b->time->tv_sec)
		return (1);
#endif
	return (strcmp(a->name, b->name));
}

static t_lst	*merge(t_lst *a, t_lst *b)
{
	t_lst	*sort;
	t_file	*fa;
	t_file	*fb;

	if (b == NULL)
		return (a);
	fa = (t_file *)a->data;
	fb = (t_file *)b->data;
	while (sort_time_then_ascii(fa, fb) >= 0)
	{
		push_lst__(&a, fb);
		pop_lst__(&b, NULL);
		if (!b)
			break ;
		fa = (t_file *)a->data;
		fb = (t_file *)b->data;
	}
	sort = a;
	while (b)
	{
		fa = (t_file *)sort->data;
		fb = (t_file *)b->data;
		if (sort_time_then_ascii(fa, fb) <= 0)
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
		}
	}
	return (a);
}

t_lst	*sort_int(t_lst **stack, size_t slen)
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
	a = sort_int(stack, slen % 2  ? (slen / 2) + 1 : slen / 2);
	b = sort_int(stack, slen / 2);
	return (merge(a, b));
}
