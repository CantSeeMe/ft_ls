/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 18:58:37 by jye               #+#    #+#             */
/*   Updated: 2017/04/14 23:17:12 by jye              ###   ########.fr       */
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
		if (strcmp(fa, fb) >= 0)
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
	while (strcmp(fa, fb) <= 0)
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

static t_lst	*sort_(t_lst **stack, size_t slen)
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
	a = sort_(stack, slen % 2 ? (slen / 2) + 1 : slen / 2);
	b = sort_(stack, slen / 2);
	return (merge(a, b));
}

static void		check_args(t_lsenv *ls, t_lst *args)
{
	t_lst	*error;
	t_stat	fstat;

	error = NULL;
	while (args)
	{
		if ((lstat(args->data, &fstat)) == -1)
			push_lst__(&error, args->data);
		else if (S_ISDIR(fstat.st_mode))
			push_lst__(&ls->dir, args->data);
		else
			push_lst__(&ls->file, args->data);
		pop_lst__(&args, NULL);
	}
	while (error)
	{
		dprintf(2, "%s: %s: %s\n", ls->pname, error->data, strerror(ENOENT));
		pop_lst__(&error, NULL);
	}
}

void			set_ls_args(t_lsenv *ls, int ac, char **av)
{
	t_lst	*args;
	t_stat	fstat;
	size_t	slen;
	char	*path;

	args = NULL;
	slen = 0;
	memset(ls, 0, sizeof(t_lsenv));
	ls->pname = av[0];
	ls->flag = set_flag(ac, av);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ls->winsize);
	while ((path = get_arg(ac, av)))
	{
		push_lst__(&args, path);
		++slen;
	}
	if (args == NULL)
		return ;
	args = sort_(&args, slen);
	check_args(ls, args);
	if (ls->file == NULL && ls->dir == NULL) //BUG __LINE__ == 101
		push_lst__(&ls->dir, CWD);
	else if ((ls->dir && ls->file) || (ls->dir->next)) // SIEGV
		ls->flag |= show_folder;
}
