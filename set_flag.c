/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:08:07 by jye               #+#    #+#             */
/*   Updated: 2017/04/16 02:37:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	usage(char *prog_name)
{
	(void)prog_name;
	exit(EXIT_FAILURE);
}

int			set_flag(int ac, char **av)
{
	char	c;
	int		flag;

	flag = 0;
	while ((c = get_opt(ac, av, LS_FLAGS)) != -1)
	{
		if (c == 'l')
			flag |= ell;
		else if (c == '1')
			flag |= one;
		else if (c == 'R')
			flag |= recursive;
		else if (c == 'r')
			flag |= rever_sort;
		else if (c == 'a')
			flag |= show_all;
		else if (c == 't')
			flag |= mtim;
		else if (c == 'u')
			flag = (flag & ctim ? flag ^ ctim : flag) | atim;
		else if (c == 'U')
			flag = (flag & atim ? flag ^ atim : flag) | ctim;
		else if (c == 'f')
			flag = (flag & 0) | (no_sort | show_all);
		else if (c == 'h')
			flag |= human_size;
		else if (c == 'G')
			flag |= color;
		else
			usage(av[0]);
	}
	if (!isatty(STDOUT_FILENO))
		flag = (flag & ~(color)) | one;
	return (flag);
}
