/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/spool/mail/root>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 23:18:01 by root              #+#    #+#             */
/*   Updated: 2017/04/11 23:18:10 by root             ###   ########.fr       */
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
			if (cur_ac[av][0] != '-')
				break ;
			cur_ac += 1;
		}
	}
	if (cur_ac[av] != NULL)
		return (cur_ac++[av]);
	else
		return (NULL);
}
