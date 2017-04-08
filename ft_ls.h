/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:04:26 by jye               #+#    #+#             */
/*   Updated: 2017/04/08 22:53:38 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h> // window size
# include <sys/stat.h> // stat
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h> // errno
# include <limits.h>
# include <stdio.h> // strerror
# include <unistd.h> // system calls
# include <time.h> // time
# include <dirent.h> // open dir
# include <stdlib.h> // malloc
# include <string.h> // forbidden function #memset
//#include <libft.h>
//#include <ft_printf.h>

# define SIX_MONTH_SEC 15552000
# define IS_TOO_OLD(timespec) ((timespec) > SIX_MONTH_SEC)
# define IS_TOO_NEW(timespec) ((timespec) > SIX_MONTH_SEC)
# define CWD "."

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct winsize	t_winsize;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_lst
{
	struct s_lst	*prev;
	struct s_lst	*next;
	void			*data;
}						t_lst;

typedef struct			s_file
{
	t_dirent	*cf_;
	t_stat		*cf_stat_;
	t_passwd	*user_;
	t_group		*group_;
	char		sym_link[PATH_MAX];
	char		perm[12];
}						t_file;

/*
** get_opt
*/
int						get_opt(int ac, char **av, char *known_flag);

/*
** lst
*/
t_lst					*init_lst__(void *data);
void					push_lst__(t_lst **node, void *data);
void					pop_lst__(t_lst **node, void (*del)());
void					append_lst__(t_lst *node, void *data);

#endif
