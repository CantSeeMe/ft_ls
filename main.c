/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/18 02:56:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_cwd(t_cdir *cdir, t_lsenv *ls)
{
	DIR			*cwd;
	t_lst		*cwd_file;
	t_file		*file;
	t_dirent	*cfile;
	size_t		flen;
	size_t		nb_file;

	if ((cwd = cdir->cwd) == NULL)
	{
		dprintf(2, "%s: %s: %s\n", ls->pname,
									cdir->cur_path,
									strerror(cdir->errno_));
		return ;
	}
	if ((cdir->cwd_file = init_lst__(NULL)) == NULL)
	{
		dprintf(2, "%s: line %d:  malloc failed", ls->pname, __LINE__ - 2);
		return ;
	}
	cwd_file = cdir->cwd_file;
	nb_file = 0;
	while ((cfile = readdir(cwd)) != NULL)
	{
		errno = 0;
		if (cfile->d_name[0] == '.' && !(ls->flag & show_all))
			continue ;
		flen = strlen(cfile->d_name);
		if (cdir->max_len < flen)
			cdir->max_len = flen;
		if ((file = init_file__(cdir, cfile, ls)) == NULL)
		{
			perror(ls->pname);
			continue ;
		}
		if (lstat(file->path_to_file, &file->stat) == -1)
		{
			perror(ls->pname);
			free_file(file);
			continue ;
		}
		if (ls->flag & (TIME_FLAG | ell))
			set_timespec(file, ls);
		append_lst__(cwd_file, file);
		cwd_file = cwd_file->next;
		nb_file += 1;
	}
	cdir->cwd_nb_file = nb_file;
	pop_lst__(&cdir->cwd_file, NULL);
}

void	list_dir_(t_lsenv *ls)
{
	t_cdir	*cdir;

	if ((cdir = init_dir__(ls->dir->data, ls)) == NULL)
		return ;
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
	if (ls->flag & mtim)
		cdir->cwd_file = sort_int(&cdir->cwd_file, cdir->cwd_nb_file);
	else if (!(ls->flag & no_sort))
		cdir->cwd_file = sort_ascii(&cdir->cwd_file, cdir->cwd_nb_file);
	print_list(cdir, ls);
	free_cdir(cdir);
}

void	list_args(t_lsenv *ls)
{
	t_cdir	*cdir;
	t_file	*file;
	t_lst	*args;
	t_lst	*cp_ar;
	size_t	slen;

	cdir = malloc(sizeof *cdir);
	memset(cdir, 0, sizeof *cdir);
	args = ls->file;
	cdir->cwd_file = init_lst__(NULL);
	cp_ar = cdir->cwd_file;
	while (args)
	{
		file = malloc(sizeof *file);
		file->path_to_file = NULL;
		file->name = (char *)args->data;
		slen = strlen(file->name);
		if (cdir->max_len < slen)
			cdir->max_len = slen;
		lstat(file->name, &file->stat);
		if (ls->flag & (TIME_FLAG | ell))
			set_timespec(file, ls);
		pop_lst__(&args, NULL);
		append_lst__(cp_ar, file);
		cp_ar = cp_ar->next;
		cdir->cwd_nb_file += 1;
	}
	pop_lst__(&cdir->cwd_file, NULL);
	ls->file = NULL;
	print_list(cdir, ls);
	free_cdir(cdir);
}

void	list_dir(t_lsenv *ls)
{
	if (ls->file)
	{
		list_args(ls);
		if (ls->dir)
			printf("\n");
	}
	while (ls->dir)
	{
		if (ls->flag & show_folder)
			printf("%s:\n",ls->dir->data);
		list_dir_(ls);
		pop_lst__(&ls->dir, NULL);
		if (ls->dir)
			printf("\n");
	}
}

/* -------------------------------------------- */
/* -------------------------------------------- */
/* -------------------------------------------- */

t_lst	*get_dir_to_list(t_lsenv *ls)
{
	t_cdir	*cdir;
	t_lst	*args;
	t_lst	*ldir;
	t_lst	*ldir_ape;

	args = ls->dir;
	if ((ldir = init_lst__(NULL)) == NULL)
	{
		dprintf(STDERR_FILENO, "%s: line %d: malloc failed\n",
				ls->pname,
				__LINE__ - 2);
		exit(EXIT_FAILURE);
	}
	ldir_ape = ldir;
	ls->dir = NULL;
	while (args)
	{
		if ((cdir = init_dir__(args->data, ls)) == NULL)
		{
			dprintf(STDERR_FILENO, "%s: line %d: malloc failed, cannot" \
					" list directory %s\n",
					ls->pname,
					__LINE__ - 2,
					args->data);
			exit(EXIT_FAILURE);
		}
		append_lst__(ldir_ape, cdir);
		ldir_ape = ldir_ape->next;
		pop_lst__(&args, NULL);
	}
	pop_lst__(&ldir, NULL);
	return (ldir);
}

void	go_git_gud(t_cdir *cdir, t_lst *cur_dir_to_list, t_lsenv *ls)
{
	t_lst	*a;
	t_lst	*cwd_file;
	t_file	*file;
	t_cdir	*new_;

	if (cdir->cwd_nb_file == 0)
		return ;
	if (ls->flag & mtim)
		cdir->cwd_file = sort_int(&cdir->cwd_file, cdir->cwd_nb_file);
	else if (!(ls->flag & no_sort))
		cdir->cwd_file = sort_ascii(&cdir->cwd_file, cdir->cwd_nb_file);
	cwd_file = cdir->cwd_file;
	a = cur_dir_to_list;
	while (cwd_file)
	{
		file = (t_file *)cwd_file->data;
		if (S_ISDIR(file->stat.st_mode) && strcmp(file->name, CWD) && strcmp(file->name, ".."))
		{
			if ((new_ = init_dir__(file->path_to_file, ls)) == NULL)
			{
				cwd_file = cwd_file->next;
				continue ;
			}
			append_lst__(a, new_);
			a = a->next;
		}
		cwd_file = cwd_file->next;
	}
}

void	list_rdir(t_lsenv *ls)
{
	t_lst	*cur_dir_to_list;
	t_lst	*new_entry;
	t_cdir	*cdir;

	if (ls->file)
	{
		list_args(ls);
		if (ls->dir)
			printf("\n");
	}
	cur_dir_to_list = get_dir_to_list(ls);
	while (cur_dir_to_list)
	{
		cdir = (t_cdir *)cur_dir_to_list->data;
		if (ls->flag & show_folder)
			printf("%s:\n", cdir->cur_path);
		read_cwd(cdir, ls);
		go_git_gud(cdir, cur_dir_to_list, ls);
		print_list(cdir, ls);
		pop_lst__(&cur_dir_to_list, &free_cdir);
		if (cur_dir_to_list)
			printf("\n");
	}
}

int		main(int ac, char **av)
{
	t_lsenv	ls;

	set_ls_args(&ls, ac, av);
/* #ifdef __APPLE__ */
/* 	if (ls.flag & color) */
/* 		set_color(&ls); */
/* #endif */
	if (ls.flag & recursive)
		list_rdir(&ls);
	else
		list_dir(&ls);
	return (0);
}
