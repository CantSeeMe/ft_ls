/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/12 02:22:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_cdir	*init_dir__(char *path, t_lsenv *ls)
{
	t_cdir	*new_;

	errno = 0;
	if ((new_ = malloc(sizeof(t_cdir))) == NULL)
		return (NULL);
	if ((new_->cwd = opendir(path)) == NULL)
	{
		perror(ls->pname);
		free(new_);
		return (NULL);
	}
	if ((new_->cur_path_name = strdup(path)) == NULL)
	{
		perror(ls->pname);
		free(new_->cwd);
		free(new_);
		return (NULL);
	}
	new_->cwd_file = NULL;
	return (new_);
}

void	read_cwd(t_cdir *cdir)
{
	t_lst		*cwd_file;
	t_file		*file_data;
	t_dirent	*cfile;
	t_stat		*fstat;
	t_
}

void	list_dir_(char *path, t_lsenv *ls)
{
	t_cdir	*cdir;

	if ((cdir = init_dir__(path, ls)) == NULL)
		return ;
	/* if (ls->flag & (mtim | atim | ctim | color | ell)) */
	/* 	readell_cwd(cdir); */
	/* else */
		read_cwd(cdir);
	if (ls->flag & no_sort)
	{
		/* print_list(cdir, ls); */
		return ;
	}
	/* sort_list(path, ls); */
	/* print_list(cdir, ls); */
}

void	list_dir(char *path, t_lsenv *ls)
{
	if (S_ISDIR(fstat->st_mode))
	{
		/* if (flag & recursive) */
		/* 	rlist_dir_(path, flag); */
		/* else */
		list_dir_(path, ls);
		return ;
	}
}

/* void	set_color(t_lsenv *ls) */
/* { */
/* 	char	*lscolors; */

/* 	lscolors = getenv("LSCOLORS"); */
/* } */

int		main(int ac, char **av)
{
	char	*args;
	t_lsenv	ls;

	ls.flag = set_flag(ac, av);
	ls.arg = NULL;
/* #ifdef __APPLE__ */
/* 	if (ls.flag & color) */
/* 		set_color(&ls); */
/* #endif */
	if ((args = get_arg(ac, av)) == NULL)
		list_dir(CWD, &ls);
	return (0);
}
