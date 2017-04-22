/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:20:12 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:45:42 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		error___(void)
{
	ft_dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
	exit(EXIT_BIG_FAILURE);
}

static t_file	*read_arg_(char *path, t_cdir *cdir, t_lsenv *ls)
{
	size_t	slen;
	t_file	*file;

	if ((file = malloc(sizeof(*file))) == NULL)
		error___();
	file->path_to_file = NULL;
	file->name = path;
	slen = ft_strlen(file->name);
	file->nlen = slen;
	file->fcolor = NONE;
	file->bcolor = NONE;
	if (cdir->max_len < slen)
		cdir->max_len = slen;
	if ((lstat(path, &file->stat)) == -1)
	{
		file->errno_ = 1;
		ft_dprintf(2, "%s: %s: %s\n", ls->pname, file->path_to_file,
				strerror(errno));
		free_file(file);
		return (NULL);
	}
	if (ls->flag & (TIME_FLAG | ell | color))
		set_var(cdir, file, ls);
	return (file);
}

void			list_args(t_lsenv *ls)
{
	t_cdir	*cdir;
	t_lst	*args;
	t_lst	*cp_ar;
	t_file	*file;

	cdir = malloc(sizeof(*cdir));
	ft_memset(cdir, 0, sizeof(*cdir));
	args = ls->file;
	cdir->cwd_file = init_lst__(NULL);
	cp_ar = cdir->cwd_file;
	while (args)
	{
		if ((file = read_arg_(args->data, cdir, ls)) == NULL)
			continue ;
		append_lst__(cp_ar, file);
		pop_lst__(&args, NULL);
		cp_ar = cp_ar->next;
		cdir->cwd_nb_file += 1;
	}
	pop_lst__(&cdir->cwd_file, NULL);
	ls->file = NULL;
	cdir->cwd_file = sort_(&cdir->cwd_file, cdir->cwd_nb_file, ls->flag);
	print_list(cdir, ls);
	free_cdir(cdir);
}

static t_file	*read_file_(t_cdir *cdir, t_dirent *cfile, t_lsenv *ls)
{
	t_file	*file;
	size_t	flen;

	errno = 0;
	if (cfile->d_name[0] == '.' && !(ls->flag & show_all))
		return (NULL);
	flen = ft_strlen(cfile->d_name);
	if (cdir->max_len < flen)
		cdir->max_len = flen;
	file = init_file__(cdir, cfile, ls);
	file->nlen = flen;
	if (lstat(file->path_to_file, &file->stat) == -1)
	{
		file->errno_ = 1;
		ft_dprintf(2, "%s: %s: %s\n", ls->pname, file->path_to_file,
				strerror(errno));
		free_file(file);
		return (NULL);
	}
	if (ls->flag & (TIME_FLAG | ell | color))
		set_var(cdir, file, ls);
	return (file);
}

void			read_cwd(t_cdir *cdir, t_lsenv *ls)
{
	t_lst		*cwd_file;
	t_file		*file;
	t_dirent	*cfile;

	if (cdir->cwd == NULL)
	{
		ft_dprintf(2, "%s: %s: %s\n", ls->pname, cdir->cur_path,
				strerror(cdir->errno_));
		return ;
	}
	if ((cwd_file = init_lst__(NULL)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
		exit(EXIT_BIG_FAILURE);
	}
	cdir->cwd_file = cwd_file;
	while ((cfile = readdir(cdir->cwd)) != NULL)
	{
		if ((file = read_file_(cdir, cfile, ls)) == NULL)
			continue ;
		append_lst__(cwd_file, file);
		cwd_file = cwd_file->next;
		cdir->cwd_nb_file += 1;
	}
	pop_lst__(&cdir->cwd_file, NULL);
}
