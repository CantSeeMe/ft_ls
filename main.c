/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/14 23:14:26 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_cdir	*init_dir__(char *path, t_lsenv *ls)
{
	t_cdir	*new_;

	errno = 0;
	if ((new_ = malloc(sizeof(t_cdir))) == NULL)
		return (NULL);
	memset(new_, 0, sizeof(t_cdir));
	if ((new_->cwd = opendir(path)) == NULL)
	{
		perror(ls->pname);
		free(new_);
		return (NULL);
	}
	if ((new_->cur_path_name = strdup(path)) == NULL)
	{
		perror(ls->pname);
		free(new_->cwd);
		free(new_);
		return (NULL);
	}
	new_->cwd_file = NULL;
	return (new_);
}

char	*cat_path_file(char *cur_dir, char *file)
{
	char	*path;
	size_t	cd_len;
	size_t	f_len;

	cd_len = strlen(cur_dir);
	f_len = strlen(file);
	if ((path = malloc(cd_len + f_len + 2)) == NULL)
		return (NULL);
	memset(path, 'c', cd_len + f_len + 2);
	memcpy(path, cur_dir, cd_len);
	cd_len[path] = '/';
	memcpy(path + cd_len + 1, file, f_len);
	(cd_len + f_len + 1)[path] = 0;
	return (path);
}

t_file	*init_file__(t_cdir *cdir, t_dirent *cfile)
{
	t_file	*new_;

	errno = 0;
	if ((new_ = malloc(sizeof(t_file))) == NULL)
		return (NULL);
	memset(new_, 0, sizeof(t_file));
	if (!(new_->path_file = cat_path_file(cdir->cur_path_name, cfile->d_name)))
	{
		free(new_);
		return (NULL);
	}
	new_->file = cfile;
	return (new_);
}

int		init_fstat__(t_file *file_data)
{
	t_stat	*fstat_;

	if ((fstat_ = malloc(sizeof(t_stat))) == NULL)
		return (1);
	if ((lstat(file_data->path_file, fstat_)) == -1)
		return (1);
	file_data->file_stat = fstat_;
	return (0);
}

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
		if ((file_data = init_file__(cdir, cfile)) == NULL)
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
	if (ls->flag & no_sort)
	{
		print_list(cdir, ls);
		return ;
	}
	/* if (ls->flag & (atim | ctim | mtim)) */
	/* 	cdir->cwd_file = sort_int(&cdir->cwd_file, cdir->cwd_nb_file) */
	/* else */
		cdir->cwd_file = sort_ascii(&cdir->cwd_file, cdir->cwd_nb_file);
	print_list(cdir, ls);
}

void	print_args_(t_cdir *cdir, t_lsenv *ls)
{
	int		x;
	int		i;
	int		o;
	int		pad;
	t_lst	*t;

	x = ls->winsize.ws_col / (cdir->max_len + MIN_WIDTH);
	o = cdir->cwd_nb_file / x;
	pad = cdir->max_len + MIN_WIDTH;
	t = cdir->cwd_file;
	i = 0;
	while (t)
	{
		t_file *z = (t_file *)t->data;
		printf("%*s", -pad, z->path_file);
		++i;
		t = t->next;
		if (i == o)
		{
			i = 0;
			printf("\n");
		}
	}
	if (i)
		printf("\n");
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
		file->path_file = (char *)args->data;
		slen = strlen(file->path_file);
		if (cdir->max_len < slen)
			cdir->max_len = slen;
		file->file_stat = malloc(sizeof(t_stat));
		lstat(file->path_file, file->file_stat);
		pop_lst__(&args, NULL);
		append_lst__(cp_ar, file);
		cp_ar = cp_ar->next;
	}
	pop_lst__(&cdir->cwd_file, NULL);
	ls->file = NULL;
	print_args_(cdir, ls);
}

void	list_dir(t_lsenv *ls)
{
	if (ls->file)
	{
		list_args(ls);
		if (ls->dir)
			printf("\n");
	}
	printf("%p %p\n", ls->file, ls->dir);
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
	char	*args;
	t_lsenv	ls;

	set_ls_args(&ls, ac, av);
/* #ifdef __APPLE__ */
/* 	if (ls.flag & color) */
/* 		set_color(&ls); */
/* #endif */
	/* if (ls->flag & recursive) */
	/* 	list_rdir(&ls); */
	/* else */
	list_dir(&ls);
	return (0);
}
