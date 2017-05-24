/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:44:24 by jye               #+#    #+#             */
/*   Updated: 2017/05/24 21:25:55 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		intlen(long integer)
{
	int	z;

	z = 1;
	while (integer > 9)
	{
		integer /= 10;
		++z;
	}
	return (z);
}

void	long_format(t_file *file, int i[4])
{
	if (S_ISCHR(file->stat.st_mode) || S_ISBLK(file->stat.st_mode))
		ft_printf("%s %*d %*s %*s %*d,%5d %s %s%s%s%s %s %s\n",
				perm_format(file->stat.st_mode, file->path_to_file),
				i[2], file->stat.st_nlink,
				-(i[0]), file->pw_name,
				-(i[1]), file->gr_name,
				i[3] - 6, file->stat.st_rdev >> 24,
				file->stat.st_rdev & 0377,
				time_format(file->time->tv_sec),
				file->fcolor, file->bcolor,
				file->name, *file->fcolor ? RESET_ATTR : NONE,
				file->sym > 0 ? "->" : "",
				file->sym > 0 ? file->sym_link : "");
	else
		ft_printf("%s %*d %*s %*s %*lld %s %s%s%s%s %s %s\n",
				perm_format(file->stat.st_mode, file->path_to_file),
				i[2], file->stat.st_nlink,
				-(i[0]), file->pw_name,
				-(i[1]), file->gr_name,
				i[3], file->stat.st_size,
				time_format(file->time->tv_sec),
				file->fcolor, file->bcolor,
				file->name, *file->fcolor ? RESET_ATTR : NONE,
				file->sym > 0 ? "->" : "",
				file->sym > 0 ? file->sym_link : "");
}

void	print_ell(t_cdir *cdir)
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
	nlink_pad = intlen(cdir->nlink);
	size_pad = intlen(cdir->size);
	if (cdir->spe_ && size_pad < 9)
		size_pad = 9;
	if (cwd_file)
		ft_printf("total %lld\n", cdir->block);
	while (cwd_file)
	{
		long_format(cwd_file->data,
					(int[4]){pw_pad, gr_pad, nlink_pad, size_pad});
		cwd_file = cwd_file->next;
	}
}
