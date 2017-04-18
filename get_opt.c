/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 22:38:56 by jye               #+#    #+#             */
/*   Updated: 2017/04/18 01:36:27 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	unknow_flag(char *pname, char c)
{
	dprintf(2 ,"%s: invalid option -- '%c'\n", pname, c);
	return ('?');
}

int			get_opt(int ac, char **av, char *known_flag)
{
	static char	*nextchar = NULL;
	static int	current_ac = 0;
	char		c;

	if (current_ac == -1)
		return (-1);
	if (nextchar == NULL || *nextchar == 0)
	{
		current_ac += 1;
		if (current_ac >= ac || av[current_ac][0] != '-')
			return (-1);
		nextchar = av[current_ac] + 1;
		if (*nextchar == '-')
			return (-1);
	}
	c = *nextchar++;
	if (!c)
	{
		current_ac = -1;
		return (-1);
	}
	if (strchr(known_flag, c) == NULL)
		return (unknow_flag(av[0], c));
	return (c);
}
