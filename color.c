/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 22:25:52 by jye               #+#    #+#             */
/*   Updated: 2017/04/21 22:52:36 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_color_env(const char **lscolors)
{
	char	*env_var;
	char	*default_;
	size_t	i;

	env_var = getenv("LSCOLORS");
	default_ = DEFAULT_LSCOLORS;
	i = 0;
	while (env_var[i])
	{
		if (env_var[i] != 'x')
			lscolors[i] = g_ls_fcolor[INDEX_HASH(env_var[i])];
		else
			lscolors[i] = NONE;
		printf("%d %c\n", INDEX_HASH(env_var[i]), env_var[i]);
		++i;
		if (!env_var[i])
			break ;
		if (env_var[i] != 'x')
			lscolors[i] = g_ls_bcolor[INDEX_HASH(env_var[i])];
		else
			lscolors[i] = NONE;
		printf("%d %c\n", INDEX_HASH(env_var[i]), env_var[i]);
		++i;
	}
	printf("\n");
}

char	*get_color(dev_t st_mode)
{
	static const char	*lscolors[22];

	if (lscolors[0] == NULL)
		set_color_env(lscolors);
	printf("%s lscolors %s", lscolors[0], RESET_ATTRIBUTE);
	return (NULL);
}

int		main(int ac, char **av)
{
	get_color(0);
	return (0);
}
