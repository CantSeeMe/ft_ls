/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:22:04 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 03:29:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_file_type(register const mode_t st_mode)
{
	if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	else
		return ('-');
}

#ifdef __APPLE__

static int	get_xattr(const char *path)
{
	acl_t	acl;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)) != NULL)
	{
		acl_free(acl);
		return ('+');
	}
	else
		return (' ');
}

#endif

char		*perm_format(register const mode_t st_mode, const char *path)
{
	static char	perm[12] = {0};

	0[perm] = get_file_type(st_mode);
	1[perm] = st_mode & S_IRUSR ? 'r' : '-';
	2[perm] = st_mode & S_IWUSR ? 'w' : '-';
	if (st_mode & S_ISUID)
		3[perm] = (st_mode & (S_IXUSR)) ? 's' : 'S';
	else
		3[perm] = st_mode & S_IXUSR ? 'x' : '-';
	4[perm] = st_mode & S_IRGRP ? 'r' : '-';
	5[perm] = st_mode & S_IWGRP ? 'w' : '-';
	if (st_mode & S_ISGID)
		6[perm] = (st_mode & (S_IXGRP)) ? 's' : 'S';
	else
		6[perm] = st_mode & S_IXGRP ? 'x' : '-';
	7[perm] = st_mode & S_IROTH ? 'r' : '-';
	8[perm] = st_mode & S_IWOTH ? 'w' : '-';
	if (st_mode & S_ISVTX)
		9[perm] = (st_mode & (S_IXOTH)) ? 't' : 'T';
	else
		9[perm] = st_mode & S_IXOTH ? 'x' : '-';
//	10[perm] = get_xattr(path);
	return (perm);
}
