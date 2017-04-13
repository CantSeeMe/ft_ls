/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <jye@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 20:03:32 by root              #+#    #+#             */
/*   Updated: 2017/04/13 21:44:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_(t_cdir *cdir, t_lsenv *ls)
{
	int		x;
	int		i;
	int		pad;
	t_lst	*t;

	x = ls->winsize.ws_col / (cdir->max_len + MIN_WIDTH);
	pad = cdir->max_len + MIN_WIDTH;
	printf("x:%d  maxn_len:%lu ws_col:%lu\n", x, cdir->max_len + MIN_WIDTH, ls->winsize.ws_col);
	t = cdir->cwd_file;
	while (t)
	{
		t_file *z = (t_file *)t->data;
		printf("%*s", -pad, z->file->d_name);
		++i;
		t = t->next;
		if (i == x)
		{
			i = 0;
			printf("\n");
		}
	}
	if (i)
		printf("\n");
		
}

void	print_list(t_cdir *cdir, t_lsenv *ls)
{
	/* if (ls->flag & one) */
	/* 	print_one_(cdir, ls); */
	/* else if (ls->flag & ell) */
	/* 	print_ell_(cdir, ls); */
	/* else */
		print_list_(cdir, ls);
}
