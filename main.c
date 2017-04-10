/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/10 18:23:18 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	DIR			*cwd;
	t_dirent	*cf;
	t_stat		*cf_stat;
	t_file		*file_data;

	cwd = opendir(CWD);
	(void)ac;
	(void)av;
	while ((cf = readdir(cwd)) != NULL)
	{
		file_data = malloc(sizeof *file_data);
		memset(file_data, 0, sizeof *file_data);
		file_data->cur_file = cf;
		cf_stat = malloc(sizeof *cf_stat);
		memset(cf_stat, 0, sizeof *cf_stat);
		lstat(cf->d_name, cf_stat);
		file_data->cur_file_stat = cf_stat;
		if (S_ISLNK(cf_stat->st_mode))
			readlink(cf->d_name, file_data->sym_link, PATH_MAX);
		perm_format(cf_stat->st_mode, file_data->perm);
		file_data->user = getpwuid(cf_stat->st_uid);
		file_data->group = getgrgid(cf_stat->st_gid);
#ifdef __linux__
		time_format(cf_stat->st_mtim.tv_sec, file_data->human_time);
#elif __APPLE__
		time_format(cf_stat->st_mtimespec.tv_sec, file_data->human_time);
#endif
		acl_t	acl = NULL;
		if (!S_ISLNK(cf_stat->st_mode))
		{
#ifdef __linux__
			errno = 0;
			acl = acl_get_file(cf->d_name, ACL_TYPE_ACCESS);
			if (acl && errno == ENODATA)
			{
				acl_free(acl);
				acl = NULL;
				errno = 0;
			}
#elif __APPLE__
			acl = acl_get_file(cf->d_name, ACL_TYPE_EXTENDED);
#endif
		}
		printf("%s%s %s\n", file_data->perm, acl ? "+" : "", cf->d_name);
		if (acl)
			acl_free(acl);
	}
	return (0);
}
