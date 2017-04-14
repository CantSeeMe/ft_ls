/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <jye@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 20:03:32 by root              #+#    #+#             */
/*   Updated: 2017/04/14 23:12:37 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_(t_cdir *cdir, t_lsenv *ls)
{
	t_lst	*t;
	t_file	*z;
	int		x;
	int		o;
	int		i;
	int		pad;

	x = ls->winsize.ws_col / (cdir->max_len + MIN_WIDTH);
//	o = x * cdir->cwd_nb_file /;
//	printf("%d\n", o);
	pad = cdir->max_len + MIN_WIDTH;
	t = cdir->cwd_file;
	i = 0;
	while (t)
	{
		z = (t_file *)t->data;
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
