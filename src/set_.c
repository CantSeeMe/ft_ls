/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:25:50 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:44:56 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_symlink(t_file *file)
{
	errno = 0;
	file->sym = readlink(file->path_to_file, file->sym_link, PATH_MAX);
	if (file->sym > 0)
		file->sym[file->sym_link] = 0;
	else
		ft_dprintf(STDERR_FILENO, "ft_ls: cannot read symbolic link '%s': %s\n",
				file->path_to_file,
				strerror(errno));
}

static void	set_var_(t_cdir *cdir, t_file *file, t_stat *fstat)
{
	size_t len;

	len = ft_strlen(file->gr_name);
	if (len > cdir->gr_len)
		cdir->gr_len = len;
	len = ft_strlen(file->pw_name);
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

void		set_var(t_cdir *cdir, t_file *file, t_lsenv *ls)
{
	t_group		*group;
	t_passwd	*user;
	t_stat		*fstat;

	if (ls->flag & ell)
	{
		fstat = &file->stat;
		group = getgrgid(fstat->st_gid);
		user = getpwuid(fstat->st_uid);
		file->gr_name = ft_strdup(group->gr_name);
		file->pw_name = ft_strdup(user->pw_name);
		set_var_(cdir, file, fstat);
	}
	set_timespec(file, ls);
	if (ls->flag & color)
		set_color(file);
}
