/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:13:46 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 19:35:35 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_file(t_file *file)
{
	if (file->path_to_file)
	{
		free(file->name);
		free(file->path_to_file);
	}
	if (!file->errno_)
	{
		free(file->gr_name);
		free(file->pw_name);
	}
	free(file);
}

void	free_cdir(t_cdir *cdir)
{
	t_lst	*to_free;

	to_free = cdir->cwd_file;
	while (to_free)
		pop_lst__(&to_free, &free_file);
	free(cdir->cur_path);
	if (cdir->cwd)
		closedir(cdir->cwd);
	free(cdir);
}
