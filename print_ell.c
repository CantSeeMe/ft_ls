/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:44:24 by jye               #+#    #+#             */
/*   Updated: 2017/04/18 22:52:38 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ell(t_cdir *cdir, t_lsenv *ls)
{
	t_lst	*cwd_file;
	t_group	*gr;
	t_passwd *uid;
	int		pw_pad;
	int		gr_pad;
	int		size_pad;
	int		nlink_pad;

	if (cdir->errno_)
		return ;
	cwd_file = cdir->cwd_file;
	pw_pad = cdir->pw_len + MIN_WIDTH;
	gr_pad = cdir->gr_len + MIN_WIDTH;
	nlink_pad = cdir->nlink_len + MIN_WIDTH;
	size_pad = cdir->size_len + MIN_WIDTH;
	printf("total %lld\n", cdir->block);
	while (cwd_file)
	{
		t_file	*file = cwd_file->data;
		uid = getpwuid(file->stat.st_uid);
		gr = getgrgid(file->stat.st_gid);
		printf("%s %*d %*s %*s %*lld %s %s %s %s\n",
			   perm_format(file->stat.st_mode, file->path_to_file),
			   nlink_pad, file->stat.st_nlink,
			   -pw_pad, uid->pw_name,
			   -gr_pad, gr->gr_name,
			   size_pad, file->stat.st_size,
			   time_format(file->time->tv_sec),
			   file->name,
			   S_ISLNK(file->stat.st_mode) ? "->" : "",
			   S_ISLNK(file->stat.st_mode) ? file->sym_link : "");
		cwd_file = cwd_file->next;
	}
}
