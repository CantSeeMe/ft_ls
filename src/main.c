/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:54:32 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 18:28:04 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_lsenv	ls;

	set_ls_args(&ls, ac, av);
	if (ls.flag & color)
		set_color_env();
	if (ls.flag & recursive)
		list_rdir(&ls);
	else
		list_dir(&ls);
	return (0);
}
