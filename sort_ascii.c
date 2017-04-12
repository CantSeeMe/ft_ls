/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:22:58 by jye               #+#    #+#             */
/*   Updated: 2017/04/12 22:25:37 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst	*merge(t_lst *a, t_lst *b)
{
	if (b == NULL)
		return (a);
	while (b)
	{
		
	}
}

t_lst	*sort_ascii(t_lst **stack, size_t slen)
{
	t_lst	*a;
	t_lst	*b;

	a = NULL;
	b = NULL;
	if (slen < 3)
	{
		push_lst__(&a, (*stack)->data);
		pop_lst__(stack, NULL);
		if (*stack != NULL)
		{
			push_lst__(&b, (*stack)->data);
			pop_lst__(stack, NULL);
		}
		return (merge(a, b));
	}
	a = sort_ascii(stack, slen / 2);
	b = sort_ascii(stack, slen / 2);
	return (merge(a, b));
}
