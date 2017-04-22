/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_timespec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 18:18:14 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 18:05:26 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#ifdef __APPLE__
# ifdef _DARWIN_FEATURE_64_BIT_INODE

void	set_timespec(t_file *file, t_lsenv *ls)
{
	t_stat	*fstat;

	fstat = &file->stat;
	if (ls->flag & ctim)
		file->time = &fstat->st_birthtimespec;
	else if (ls->flag & atim)
		file->time = &fstat->st_atimespec;
	else
		file->time = &fstat->st_mtimespec;
}

# else

void	set_timespec(t_file *file, t_lsenv *ls)
{
	t_stat	*fstat;

	fstat = &file->stat;
	if (ls->flag & ctim)
		file->time = &fstat->st_ctimespec;
	else if (ls->flag & atim)
		file->time = &fstat->st_atimespec;
	else
		file->time = &fstat->st_mtimespec;
}

# endif
#elif __linux__

void	set_timespec(t_file *file, t_lsenv *ls)
{
	t_stat	*fstat;

	fstat = &file->stat;
	if (ls->flag & ctim)
		file->time = &fstat->st_ctim;
	else if (ls->flag & atim)
		file->time = &fstat->st_atim;
	else
		file->time = &fstat->st_mtim;
}

#endif
