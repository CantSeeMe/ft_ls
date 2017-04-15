/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <jye@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 20:03:32 by root              #+#    #+#             */
/*   Updated: 2017/04/15 23:17:59 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**format(t_cdir *cdir)
{
	char	**new_;
	t_lst	*a;
	t_file	*f;
	int		i;

	new_ = malloc((sizeof *new_) * cdir->cwd_nb_file);
	a = cdir->cwd_file;
	i = 0;
	while (a)
	{
		f = (t_file *)a->data;
		new_[i++] = f->name;
		a = a->next;
	}
	return (new_);
}

void	print_list_(t_cdir *cdir, t_lsenv *ls)
{
	char	**a;
	size_t	it = 0;
	size_t	max;
	int		skip_;
	size_t	i = 0;
	int		pad;

	a = format(cdir);
	pad = cdir->max_len + MIN_WIDTH;
	max = cdir->cwd_nb_file;
	skip_ = max / (ls->winsize.ws_col / pad) + 1;
	while (it < max)
	{
		printf("%*s", -pad, a[i]);
		i += skip_;
		if (i >= max)
		{
			printf("\n");
			i = (i % skip_) + 1;
		}
		++it;
	}
	free(a);
}

void	print_list(t_cdir *cdir, t_lsenv *ls)
{
	/* if (ls->flag & one) */
	/* 	print_one_(cdir, ls); */
	/* else if (ls->flag & ell) */
	/* 	print_ell_(cdir, ls); */
	/* else */
	t_lst	*test = cdir->cwd_file;
	while (test)
	{
		char	t[16];
		t_file *a = test->data;
		printf("%s %lu %lu %s\n", time_format(a->time->tv_sec, t), a->time->tv_sec, a->time->tv_nsec, a->name);
		test = test->next;
	}
//		print_list_(cdir, ls);
}
