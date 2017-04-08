/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 22:38:56 by jye               #+#    #+#             */
/*   Updated: 2017/04/08 02:41:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		if (av[current_ac] == NULL || av[current_ac][0] != '-')
			return (-1);
		nextchar = av[current_ac] + 1;
	}
	c = *nextchar++;
	if (!c)
	{
		current_ac = -1;
		return (-1);
	}
	if (strchr(known_flag, c) == NULL)
	{
		dprintf(2 ,"%s: invalid option -- '%c'\n", av[0], c);
		return ('?');
	}
	return (c);
}
