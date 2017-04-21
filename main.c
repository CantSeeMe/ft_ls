/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/21 22:53:08 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_symlink(t_file *file)
{
	errno = 0;
	file->sym = readlink(file->path_to_file, file->sym_link, PATH_MAX);
	if (file->sym > 0)
		file->sym[file->sym_link] = 0;
	else
		dprintf(STDERR_FILENO, "ft_ls: cannot read symbolic link '%s': %s\n",
				file->path_to_file,
				strerror(errno));
}

void	set_var_(t_cdir *cdir, t_file *file, t_stat *fstat)
{
	size_t len;

	len = strlen(file->gr_name);
	if (len > cdir->gr_len)
		cdir->gr_len = len;
	len = strlen(file->pw_name);
	if (len > cdir->pw_len)
		cdir->pw_len = len;
	if (fstat->st_size > cdir->size)
		cdir->size = fstat->st_size;
	if (fstat->st_nlink > cdir->nlink)
		cdir->nlink = fstat->st_nlink;
	if (S_ISCHR(fstat->st_mode) || S_ISBLK(fstat->st_mode))
		cdir->spe_ = 1;
	cdir->block += fstat->st_blocks;
	if (S_ISLNK(fstat->st_mode))
		set_symlink(file);
	else
		file->sym = 0;
}

void	set_var(t_cdir *cdir, t_file *file, t_lsenv *ls)
{
	t_group		*group;
	t_passwd	*user;
	t_stat		*fstat;
	size_t		len;

	if (ls->flag & ell)
	{
		fstat = &file->stat;
		group = getgrgid(fstat->st_gid);
		user = getpwuid(fstat->st_uid);
		file->gr_name = strdup(group->gr_name);
		file->pw_name = strdup(user->pw_name);
		set_var_(cdir, file, fstat);
	}
	set_timespec(file, ls);
}

t_file	*read_file_(t_cdir *cdir, t_dirent *cfile, t_lsenv *ls)
{
	t_file	*file;
	size_t	flen;

	errno = 0;
	if (cfile->d_name[0] == '.' && !(ls->flag & show_all))
		return (NULL);
	flen = strlen(cfile->d_name);
	if (cdir->max_len < flen)
		cdir->max_len = flen;
	file = init_file__(cdir, cfile, ls);
	if (lstat(file->path_to_file, &file->stat) == -1)
	{
		file->errno_ = 1;
		dprintf(2, "%s: %s: %s\n", ls->pname, file->path_to_file,
				strerror(errno));
		free_file(file);
		return (NULL);
	}
	if (ls->flag & (TIME_FLAG | ell))
		set_var(cdir, file, ls);
	return (file);
}

void	read_cwd(t_cdir *cdir, t_lsenv *ls)
{
	t_lst		*cwd_file;
	t_file		*file;
	t_dirent	*cfile;

	if (cdir->cwd == NULL)
	{
		dprintf(2, "%s: %s: %s\n", ls->pname, cdir->cur_path,
				strerror(cdir->errno_));
		return ;
	}
	if ((cwd_file = init_lst__(NULL)) == NULL)
	{
		dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
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

void	list_dir_(t_lsenv *ls)
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
	if (ls->flag & mtim)
		cdir->cwd_file = sort_int(&cdir->cwd_file, cdir->cwd_nb_file);
	else if (!(ls->flag & no_sort))
		cdir->cwd_file = sort_ascii(&cdir->cwd_file, cdir->cwd_nb_file);
	print_list(cdir, ls);
	free_cdir(cdir);
}

t_file	*read_arg_(char *path, t_cdir *cdir, t_lsenv *ls)
{
	size_t	slen;
	t_file	*file;

	if ((file = malloc(sizeof(*file))) == NULL)
	{
		dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
		exit(EXIT_BIG_FAILURE);
	}
	file->path_to_file = NULL;
	file->name = path;
	slen = strlen(file->name);
	if (cdir->max_len < slen)
		cdir->max_len = slen;
	if ((lstat(path, &file->stat)) == -1)
	{
		file->errno_ = 1;
		dprintf(2, "%s: %s: %s\n", ls->pname, file->path_to_file,
				strerror(errno));
		free_file(file);
		return (NULL);
	}
	if (ls->flag & (TIME_FLAG | ell))
		set_var(cdir, file, ls);
	return (file);
}

void	list_args(t_lsenv *ls)
{
 	t_cdir	*cdir;
	t_lst	*args;
	t_lst	*cp_ar;
	t_file	*file;

	cdir = malloc(sizeof(*cdir));
	memset(cdir, 0, sizeof(*cdir));
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
			printf("%s:\n", ls->dir->data);
		list_dir_(ls);
		pop_lst__(&ls->dir, NULL);
		if (ls->dir)
			printf("\n");
	}
}

t_lst	*get_dir_to_list(t_lsenv *ls)
{
	t_cdir	*cdir;
	t_lst	*args;
	t_lst	*ldir;
	t_lst	*ldir_ape;

	args = ls->dir;
	if ((ldir = init_lst__(NULL)) == NULL)
	{
		dprintf(STDERR_FILENO, "beep boop, can't malloc exiting...\n");
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

void	go_get_dir(t_cdir *cdir, t_lst *cur_dir_to_list, t_lsenv *ls)
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
			strcmp(file->name, CWD) &&
			strcmp(file->name, ".."))
		{
			new_ = init_dir__(file->path_to_file, ls);
			append_lst__(a, new_);
			a = a->next;
		}
		cwd_file = cwd_file->next;
	}
}

void	list_rdir(t_lsenv *ls)
{
	t_lst	*cur_dir_to_list;
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
		if (cdir->cwd_nb_file)
			go_get_dir(cdir, cur_dir_to_list, ls);
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
	if (ls.flag & recursive)
		list_rdir(&ls);
	else
		list_dir(&ls);
	return (0);
}
