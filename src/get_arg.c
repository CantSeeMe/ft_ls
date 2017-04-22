/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:43:54 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 18:43:55 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_arg(int ac, char **av)
{
	static int	cur_ac = 0;

	if (!cur_ac)
	{
		cur_ac += 1;
		while (cur_ac < ac)
		{
			if (cur_ac[av][0] == '-' && cur_ac[av][1] == '-')
			{
				cur_ac += 1;
				break ;
			}
			else if (cur_ac[av][0] == '-' && cur_ac[av][1] == 0)
				break ;
			else if (cur_ac[av][0] != '-')
				break ;
			cur_ac += 1;
		}
	}
	if (cur_ac[av] != NULL)
		return (cur_ac++[av]);
	else
		return (NULL);
}
