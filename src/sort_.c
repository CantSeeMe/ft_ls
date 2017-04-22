/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 18:32:36 by jye               #+#    #+#             */
/*   Updated: 2017/04/22 19:11:09 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst	*sort_(t_lst **smth, size_t nb_elem, int flag_)
{
	if (flag_ & no_sort)
		return (*smth);
	else if (flag_ & (mtim))
	{
		if (flag_ & rever_sort)
			return (rsort_int(smth, nb_elem));
		else
			return (sort_int(smth, nb_elem));
	}
	else if (flag_ & rever_sort)
		return (rsort_ascii(smth, nb_elem));
	else
		return (sort_ascii(smth, nb_elem));
}
