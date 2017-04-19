/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lsfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <jye@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 20:03:32 by root              #+#    #+#             */
/*   Updated: 2017/04/19 20:47:07 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	**format(t_lst *a, size_t cwd_nb_file)
{
	char	**new_;
	t_file	*f;
	int		i;

	if ((new_ = malloc((sizeof(*new_)) * cwd_nb_file)) == NULL)
	{
		dprintf(STDERR_FILENO, "beep boop, can't print exiting...\n");
		exit(EXIT_BIG_FAILURE);
	}
	i = 0;
	while (a)
	{
		f = (t_file *)a->data;
		new_[i++] = f->name;
		a = a->next;
	}
	return (new_);
}

static int	col(int ws_col, int it, int *pad)
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

static void	print_many_per_line(t_cdir *cdir, t_lsenv *ls)
{
	char	**a;
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

void		print_list(t_cdir *cdir, t_lsenv *ls)
{
	if (ls->flag & one)
		print_one_per_line(cdir);
	else if (ls->flag & ell)
		print_ell(cdir, ls);
	else
		print_many_per_line(cdir, ls);
}
