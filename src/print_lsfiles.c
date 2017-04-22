/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <jye@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 20:03:32 by root              #+#    #+#             */
/*   Updated: 2017/04/22 21:52:55 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	**format(t_lst *a, size_t cwd_nb_file)
{
	t_file	**new_;
	int		i;

	if ((new_ = malloc(((sizeof(*new_)) * cwd_nb_file))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "beep boop, can't print exiting...\n");
		exit(EXIT_BIG_FAILURE);
	}
	i = 0;
	while (a)
	{
		new_[i++] = a->data;
		a = a->next;
	}
	return (new_);
}

static int		col(int ws_col, int it, int *pad)
{
	int	skip_;
	int	z;

	if ((z = (ws_col / *pad)) != 0)
		skip_ = it / z + 1;
	else
	{
		skip_ = it;
		*pad = 0;
	}
	return (skip_);
}

static void		print_many_per_line(t_cdir *cdir, t_lsenv *ls)
{
	t_file	**a;
	int		pad;
	int		skip_;
	size_t	i;
	size_t	it[2];

	a = format(cdir->cwd_file, cdir->cwd_nb_file);
	pad = cdir->max_len + MIN_WIDTH;
	it[1] = cdir->cwd_nb_file;
	skip_ = col(ls->winsize.ws_col, it[1], &pad);
	i = 0;
	0[it] = 0;
	while (it[0] < it[1])
	{
		ft_printf("%s%s%s%s", a[i]->fcolor, a[i]->bcolor, a[i]->name, "\e[0m");
		ft_printf("%*s", (int)(a[i]->nlen - pad), NONE);
		i += skip_;
		if (i >= it[1])
		{
			ft_printf("\n");
			i = (i % skip_) + 1;
		}
		++it[0];
	}
	free(a);
}

static void		print_one_per_line(t_cdir *cdir)
{
	t_lst	*cwd_file;
	t_file	*file;

	cwd_file = cdir->cwd_file;
	while (cwd_file)
	{
		file = (t_file *)cwd_file->data;
		ft_printf("%s%s%s%s\n",
				file->fcolor,
				file->bcolor,
				file->name,
				*file->fcolor ? RESET_ATTR : NONE);
		cwd_file = cwd_file->next;
	}
}

void			print_list(t_cdir *cdir, t_lsenv *ls)
{
	if (ls->flag & one)
		print_one_per_line(cdir);
	else if (ls->flag & ell)
		print_ell(cdir);
	else
		print_many_per_line(cdir, ls);
}
