/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 22:25:52 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 03:46:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_default_color(int i)
{
	char	*default_;

	dprintf(STDERR_FILENO, "bad environment variable LSCOLORS\n");
	default_ = DEFAULT_LSCOLORS;
	while (default_[i])
	{
		if (default_[i] != 'x')
			g_lscolors[i] = g_ls_fcolor[INDEX_HASH(default_[i])];
		else
			g_lscolors[i] = NONE;
		++i;
		if (default_[i] != 'x')
			g_lscolors[i] = g_ls_bcolor[INDEX_HASH(default_[i])];
		else
			g_lscolors[i] = NONE;
		++i;
	}
}

static void	set_color_env(void)
{
	char	*env_var;
	size_t	i;

	env_var = getenv("G_LSCOLORS");
	i = 0;
	if (env_var)
		while (env_var[i] && strchr(G_LSCOLORS_CHAR, env_var[i]))
		{
			if (env_var[i] != 'x')
				g_lscolors[i] = g_ls_fcolor[INDEX_HASH(env_var[i])];
			else
				g_lscolors[i] = NONE;
			++i;
			if (!env_var[i] || !strchr(G_LSCOLORS_CHAR, env_var[i]))
				break ;
			if (env_var[i] != 'x')
				g_lscolors[i] = g_ls_bcolor[INDEX_HASH(env_var[i])];
			else
				g_lscolors[i] = NONE;
			++i;
		}
	if (i != 22)
		set_default_color(g_lscolors, i);
}

static int	color_mode(dev_t st_mode)
{
	if ((st_mode & ((S_ISUID | S_IXUSR))) == (S_ISUID | S_IXUSR))
		return (15);
	else if ((st_mode & ((S_ISGID | S_IXGRP))) == (S_ISGID | S_IXGRP))
		return (17);
	else if (S_ISDIR(st_mode))
		return (1);
	else if (S_ISLNK(st_mode))
		return (3);
	else if (S_ISSOCK(st_mode))
		return (5);
	else if (S_ISFIFO(st_mode))
		return (7);
	else if (st_mode & S_IXUSR)
		return (9);
	else if (S_ISBLK(st_mode))
		return (11);
	else if (S_ISCHR(st_mode))
		return (13);
	else
		return (-1);
}

void		set_color(t_file *file)
{
	int					mode;

	if ((mode = color_mode(file->stat.st_mode)) == -1)
		return ;
	file->fcolor = g_lscolors[mode - 1];
	file->bcolor = g_lscolors[mode];
}
