/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:04:26 by jye               #+#    #+#             */
/*   Updated: 2017/04/07 22:54:30 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h> // window size
# include <sys/stat.h> // stat
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <errno.h> // errno
# include <stdio.h> // strerror
# include <unistd.h> // system calls
# include <time.h> // time
# include <dirent.h> // open dir
# include <stdlib.h> // malloc
# include <string.h> // forbidden function #memset
//#include <libft.h>
//#include <ft_printf.h>

# define CWD "."

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct winsize	t_winsize;

typedef struct 			s_lst
{
	struct s_lst	*prev;
	struct s_lst	*next;
	void			*data;
}						t_lst;

/*
** get_opt
*/
int						get_opt(int ac, char **av, char *known_flag);


t_lst					*init_lst__(void *data);
void					push_lst__(t_lst **node, void *data);
void					pop_lst__(t_lst **node, void (*del)());
void					append_lst__(t_lst *node, void *data);

#endif
