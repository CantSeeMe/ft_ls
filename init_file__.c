/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file__.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:14:05 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 01:45:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*cat_path_file(char *cur_dir, char *file)
{
	char	*path;
	size_t	cd_len;
	size_t	f_len;

	cd_len = strlen(cur_dir);
	f_len = strlen(file);
	if (cd_len == 1 && *cur_dir == '/')
	{
		if ((path = malloc(cd_len + f_len + 1)) == NULL)
			return (NULL);
		memcpy(path, cur_dir, cd_len);
		memcpy(path + cd_len, file, f_len);
		(cd_len + f_len)[path] = 0;
	}
	else
	{
		if ((path = malloc(cd_len + f_len + 2)) == NULL)
			return (NULL);
		memcpy(path, cur_dir, cd_len);
		cd_len[path] = '/';
		memcpy(path + cd_len + 1, file, f_len);
		(cd_len + f_len + 1)[path] = 0;
	}
	return (path);
}

t_file		*init_file__(t_cdir *cdir, t_dirent *cfile, t_lsenv *ls)
{
	t_file	*new_;

	errno = 0;
	if ((new_ = malloc(sizeof(t_file))) == NULL)
		return (NULL);
//	memset(new_, 0, sizeof(t_file));
	if (!(new_->path_to_file = cat_path_file(cdir->cur_path ,cfile->d_name)))
	{
		free(new_);
		return (NULL);
	}
	if (!(ls->flag & ell))
	{
		new_->gr_name = NULL;
		new_->pw_name = NULL;
	}
	if (ls->flag & color)
		/* set_color(new_) */;
	else
		new_->name = strdup(cfile->d_name);
	return (new_);
}
