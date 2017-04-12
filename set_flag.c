/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/spool/mail/root>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 23:16:01 by root              #+#    #+#             */
/*   Updated: 2017/04/12 19:05:35 by jye              ###   ########.fr       */
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
			flag |= atim;
		else if (c == 'U')
			flag |= ctim;
		else if (c == 'f')
			flag |= no_sort;
		else if (c == 'h')
			flag |= human_size;
		else if (c == 'G')
			flag |= color;
		else
			usage(av[0]);
	}
	return (flag);
}
