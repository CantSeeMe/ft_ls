/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/13 21:10:26 by root             ###   ########.fr       */
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
	if ((lstat(file_data->path_file, fstat_)) == 1)
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

void	list_dir_(char *path, t_lsenv *ls)
{
	t_cdir	*cdir;

	if ((cdir = init_dir__(path, ls)) == NULL)
		return ;
	read_cwd(cdir, ls);
	if (ls->flag & no_sort)
	{
		/* print_list(cdir, ls); */
		return ;
	}
	cdir->cwd_file = sort_ascii(&cdir->cwd_file, cdir->cwd_nb_file);
	print_list(cdir, ls);
}

void	list_dir(char *path, t_lsenv *ls)
{
	/* if (S_ISDIR(fstat->st_mode)) */
	/* { */
		/* if (flag & recursive) */
		/* 	rlist_dir_(path, flag); */
		/* else */
		list_dir_(path, ls);
		return ;
	/* } */
}

/* void	set_color(t_lsenv *ls) */
/* { */
/* 	char	*lscolors; */

/* 	lscolors = getenv("LSCOLORS"); */
/* } */

int		main(int ac, char **av)
{
	char	*args;
	t_lsenv	ls;

	ls.flag = set_flag(ac, av);
	ls.arg = NULL;
	ls.pname = av[0];
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ls.winsize);
/* #ifdef __APPLE__ */
/* 	if (ls.flag & color) */
/* 		set_color(&ls); */
/* #endif */
	if ((args = get_arg(ac, av)) == NULL)
		list_dir(CWD, &ls);
	return (0);
}
