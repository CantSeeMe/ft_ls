/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 22:38:56 by jye               #+#    #+#             */
/*   Updated: 2017/04/07 22:54:47 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_opt_error(char *prog_name, char c)
{
	dprintf(2 ,"%s: illegal option -- %c\n", prog_name, c);
	return ('?');
}

int			get_opt(int ac, char **av, char *known_flag)
{
	static char	*nextchar = NULL;
	static int	current_ac;
	char		c;

	if (nextchar == NULL)
	{
		current_ac = 1;
		if (av[1] == NULL || av[current_ac][0] != '-')
			return (-1);
		nextchar = av[current_ac] + 1;
	}
	else if (*nextchar == 0)
	{
		current_ac += 1;
		if (av[current_ac] == NULL || av[current_ac][0] != '-')
			return (-1);
		nextchar = av[current_ac] + 1;
	}
	else
	{
		c = *nextchar++;
		if (strchr(known_flag, c) == NULL)
			return (get_opt_error(av[0], c));
	}
	return (c);
}
