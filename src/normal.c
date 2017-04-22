/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:27:21 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:49:09 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	list_dir_(t_lsenv *ls)
{
	t_cdir	*cdir;

	cdir = init_dir__(ls->dir->data, ls);
	read_cwd(cdir, ls);
	if (!cdir->cwd_file)
	{
		free_cdir(cdir);
		return ;
	}
	if (ls->flag & no_sort)
	{
		print_list(cdir, ls);
		return ;
	}
	cdir->cwd_file = sort_(&cdir->cwd_file, cdir->cwd_nb_file, ls->flag);
	print_list(cdir, ls);
	free_cdir(cdir);
}

void		list_dir(t_lsenv *ls)
{
	if (ls->file)
	{
		list_args(ls);
		if (ls->dir)
			ft_printf("\n");
	}
	while (ls->dir)
	{
		if (ls->flag & show_folder)
			ft_printf("%s:\n", ls->dir->data);
		list_dir_(ls);
		pop_lst__(&ls->dir, NULL);
		if (ls->dir)
			ft_printf("\n");
	}
}
