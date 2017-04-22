/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 22:08:07 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 21:49:45 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	usage(const char *prog_name)
{
	ft_dprintf(STDERR_FILENO, "%s: [-%s...] [file...]\n",
			prog_name, LS_FLAGS);
	exit(EXIT_FAILURE);
}

static int	flag_p2(char c)
{
	if (c == 'G')
		return (color);
	else if (c == '1')
		return (one);
	else if (c == 'R')
		return (recursive | show_folder);
	else if (c == 'r')
		return (rever_sort);
	else if (c == 'a')
		return (show_all);
	else if (c == 't')
		return (mtim);
	return (0);
}

int			set_flag(int ac, char **av)
{
	char	c;
	int		flag;

	flag = 0;
	while ((c = get_opt(ac, av, LS_FLAGS)) != -1)
	{
		if (c == 'u')
			flag = (flag & ~ctim) | atim;
		else if (c == 'U')
			flag = (flag & ~atim) | ctim;
		else if (c == 'f')
			flag = (flag & 0) | (no_sort | show_all);
		else if (c == 'l')
			flag = (flag & ~one) | ell;
		else if (c == '?')
			usage(av[0]);
		else
			flag |= flag_p2(c);
	}
	if (!isatty(STDOUT_FILENO))
		flag = (flag & ~(color)) | (flag & ell ? 0 : one);
	return (flag);
}
