/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <jye@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 20:03:32 by root              #+#    #+#             */
/*   Updated: 2017/04/18 20:43:12 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	**format(t_cdir *cdir)
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

static void	print_many_per_line(t_cdir *cdir, t_lsenv *ls)
{
	char	**a;
	size_t	it[2];
	int		skip_;
	size_t	i = 0;
	size_t	z;
	int		pad;

	a = format(cdir);
	pad = cdir->max_len + MIN_WIDTH;
	it[1] = cdir->cwd_nb_file;
	if ((z = (ls->winsize.ws_col / pad)) != 0)
		skip_ = it[1] / z + 1;
	else
	{
		skip_ = 1;
		pad = 0;
	}
	0[it] = 0;
	while (it[0] < it[1])
	{
		printf("%*s", -pad, a[i]);
		i += skip_;
		if (i >= it[1])
		{
			printf("\n");
			i = (i % skip_) + 1;
		}
		++it[0];
	}
	free(a);
}

static void	print_one_per_line(t_cdir *cdir)
{
	t_lst	*cwd_file;
	t_file	*file;

	cwd_file = cdir->cwd_file;
	while (cwd_file)
	{
		file = (t_file *)cwd_file->data;
		printf("%s\n", file->name);
		cwd_file = cwd_file->next;
	}
}

void	print_list(t_cdir *cdir, t_lsenv *ls)
{
	if (ls->flag & one)
		print_one_per_line(cdir);
	else if (ls->flag & ell)
		print_ell(cdir, ls);
	else
		print_many_per_line(cdir, ls);
}
