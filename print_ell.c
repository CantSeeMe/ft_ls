/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:44:24 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 03:08:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_ell(t_cdir *cdir, t_lsenv *ls)
{
	t_lst	*cwd_file;
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
		if (S_ISCHR(file->stat.st_mode) ||
			S_ISBLK(file->stat.st_mode))
			printf("%s %*d %*s %*s %*ld,%5ld %s %s %s %s\n",
				   perm_format(file->stat.st_mode, file->path_to_file),
				   nlink_pad, file->stat.st_nlink,
				   -pw_pad, file->pw_name,
				   -gr_pad, file->gr_name,
				   size_pad - 6, file->stat.st_rdev >> 8,
				   file->stat.st_rdev & 0377,
				   time_format(file->time->tv_sec),
				   file->name,
				   file->sym > 0 ? "->" : "",
				   file->sym > 0 ? file->sym_link : "");
		else
		printf("%s %*d %*s %*s %*ld %s %s %s %s\n",
			   perm_format(file->stat.st_mode, file->path_to_file),
			   nlink_pad, file->stat.st_nlink,
			   -pw_pad, file->pw_name,
			   -gr_pad, file->gr_name,
			   size_pad, file->stat.st_size,
			   time_format(file->time->tv_sec),
			   file->name,
			   file->sym > 0 ? "->" : "",
			   file->sym > 0 ? file->sym_link : "");
		cwd_file = cwd_file->next;
	}
}
