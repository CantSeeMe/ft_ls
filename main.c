/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/16 03:34:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	read_cwd(t_cdir *cdir, t_lsenv *ls)
{
	DIR			*cwd;
	t_lst		*cwd_file;
	t_file		*file_data;
	t_dirent	*cfile;
	size_t		flen;
	size_t		nb_file;

	cwd = cdir->cwd;
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
		if ((file_data = init_file__(cdir, cfile, ls)) == NULL)
		{
			perror(ls->pname);
			free(cfile);
			continue ;
		}
		if ((init_fstat__(file_data)) == 1)
		{
			perror(ls->pname);
			free(cfile);
			free(file_data);
			continue ;
		}
		if (ls->flag & (TIME_FLAG | ell))
			set_timespec(file_data, ls);
		append_lst__(cwd_file, file_data);
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
	else
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
		memset(file, 0, sizeof *file);
		file->name = (char *)args->data;
		slen = strlen(file->name);
		if (cdir->max_len < slen)
			cdir->max_len = slen;
		file->stat = malloc(sizeof(t_stat));
		lstat(file->name, file->stat);
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

int		main(int ac, char **av)
{
	t_lsenv	ls;

	set_ls_args(&ls, ac, av);
/* #ifdef __APPLE__ */
/* 	if (ls.flag & color) */
/* 		set_color(&ls); */
/* #endif */
	if (ls->flag & recursive)
		list_rdir(&ls);
	else
		list_dir(&ls);
	return (0);
}
