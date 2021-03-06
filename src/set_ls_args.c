/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ls_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:58:37 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:58:38 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		merge_p2(t_lst *sort, t_lst *b)
{
	char	*fa;
	char	*fb;

	while (b)
	{
		fa = (char *)sort->data;
		fb = (char *)b->data;
		if (ft_strcmp(fa, fb) >= 0)
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
}

static t_lst	*merge(t_lst *a, t_lst *b)
{
	char	*fa;
	char	*fb;

	if (b == NULL)
		return (a);
	fa = (char *)a->data;
	fb = (char *)b->data;
	while (ft_strcmp(fa, fb) <= 0)
	{
		push_lst__(&a, fb);
		pop_lst__(&b, NULL);
		if (!b)
			break ;
		fa = (char *)a->data;
		fb = (char *)b->data;
	}
	merge_p2(a, b);
	return (a);
}

static t_lst	*sort__(t_lst **stack, size_t slen)
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
	a = sort__(stack, slen % 2 ? (slen / 2) + 1 : slen / 2);
	b = sort__(stack, slen / 2);
	return (merge(a, b));
}

static int		set_ls_args_(t_lsenv *ls, t_lst *args)
{
	t_lst	*error;
	t_stat	fstat;

	error = NULL;
	if (args == NULL)
		return (1);
	while (args)
	{
		if ((stat(args->data, &fstat)) == -1)
			push_lst__(&error, args->data);
		else if (S_ISDIR(fstat.st_mode))
			push_lst__(&ls->dir, args->data);
		else
			push_lst__(&ls->file, args->data);
		pop_lst__(&args, NULL);
	}
	while (error)
	{
		errno = 0;
		lstat(error->data, &fstat);
		ft_dprintf(2, "%s: %s: %s\n", ls->pname, error->data, strerror(errno));
		pop_lst__(&error, NULL);
	}
	return (0);
}

void			set_ls_args(t_lsenv *ls, int ac, char **av)
{
	t_lst	*args;
	size_t	slen;
	char	*path;

	args = NULL;
	slen = 0;
	ft_memset(ls, 0, sizeof(t_lsenv));
	ls->pname = av[0];
	ls->flag = set_flag(ac, av);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ls->winsize);
	while ((path = get_arg(ac, av)))
	{
		push_lst__(&args, path);
		++slen;
	}
	if (!(ls->flag & no_sort) && args)
		args = sort__(&args, slen);
	if (set_ls_args_(ls, args))
		push_lst__(&ls->dir, CWD);
	else if ((ls->dir && ls->file) ||
			(ls->dir && ls->dir->next))
		ls->flag |= show_folder;
}
