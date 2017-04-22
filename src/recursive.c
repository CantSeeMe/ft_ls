/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:24:21 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:54:26 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lst	*get_dir_to_list(t_lsenv *ls)
{
	t_cdir	*cdir;
	t_lst	*args;
	t_lst	*ldir;
	t_lst	*ldir_ape;

	args = ls->dir;
	if ((ldir = init_lst__(NULL)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
		exit(EXIT_BIG_FAILURE);
	}
	ldir_ape = ldir;
	while (args)
	{
		cdir = init_dir__(args->data, ls);
		append_lst__(ldir_ape, cdir);
		ldir_ape = ldir_ape->next;
		pop_lst__(&args, NULL);
	}
	pop_lst__(&ldir, NULL);
	return (ldir);
}

static void		go_get_dir(t_cdir *cdir, t_lst *cur_dir_to_list, t_lsenv *ls)
{
	t_lst	*a;
	t_lst	*cwd_file;
	t_file	*file;
	t_cdir	*new_;

	if (ls->flag & mtim)
		cdir->cwd_file = sort_int(&cdir->cwd_file, cdir->cwd_nb_file);
	else if (!(ls->flag & no_sort))
		cdir->cwd_file = sort_ascii(&cdir->cwd_file, cdir->cwd_nb_file);
	cwd_file = cdir->cwd_file;
	a = cur_dir_to_list;
	while (cwd_file)
	{
		file = (t_file *)cwd_file->data;
		if (S_ISDIR(file->stat.st_mode) &&
			ft_strcmp(file->name, CWD) &&
			ft_strcmp(file->name, ".."))
		{
			new_ = init_dir__(file->path_to_file, ls);
			append_lst__(a, new_);
			a = a->next;
		}
		cwd_file = cwd_file->next;
	}
}

void			list_rdir(t_lsenv *ls)
{
	t_lst	*cur_dir_to_list;
	t_cdir	*cdir;

	if (ls->file)
	{
		list_args(ls);
		if (ls->dir)
			ft_printf("\n");
	}
	cur_dir_to_list = get_dir_to_list(ls);
	while (cur_dir_to_list)
	{
		cdir = (t_cdir *)cur_dir_to_list->data;
		if (ls->flag & show_folder)
			ft_printf("%s:\n", cdir->cur_path);
		read_cwd(cdir, ls);
		if (cdir->cwd_nb_file)
			go_get_dir(cdir, cur_dir_to_list, ls);
		print_list(cdir, ls);
		pop_lst__(&cur_dir_to_list, &free_cdir);
		if (cur_dir_to_list)
			ft_printf("\n");
	}
}
