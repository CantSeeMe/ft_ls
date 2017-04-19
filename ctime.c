/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 21:34:02 by jye               #+#    #+#             */
/*   Updated: 2017/04/19 03:32:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*time_format(const time_t file_timespec)
{
	static time_t	cur_timespec = 0;
	char			*human_time;

	if (!cur_timespec)
		time(&cur_timespec);
	human_time = ctime(&file_timespec) + 4;
	if (cur_timespec > file_timespec &&
		IS_TOO_OLD(cur_timespec - file_timespec))
	{
		memmove(human_time + 8, human_time + 16, 4);
		7[human_time] = 0x20;
		12[human_time] = 0;
	}
	else if (cur_timespec < file_timespec &&
			 IS_TOO_NEW(file_timespec - cur_timespec))
	{
		memmove(human_time + 8, human_time + 16, 4);
		7[human_time] = 0x20;
		12[human_time] = 0;
	}
	else
		12[human_time] = 0;
	return (human_time);
}
