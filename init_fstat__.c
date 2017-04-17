/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fstat__.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 20:10:14 by jye               #+#    #+#             */
/*   Updated: 2017/04/17 20:10:17 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		init_fstat__(t_file *file_data)
{
	t_stat	*fstat_;

	if ((fstat_ = malloc(sizeof(t_stat))) == NULL)
		return (1);
	if ((lstat(file_data->path_to_file, fstat_)) == -1)
		return (1);
	file_data->stat = fstat_;
	return (0);
}
