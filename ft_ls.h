/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:04:26 by jye               #+#    #+#             */
/*   Updated: 2017/04/12 02:22:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h> // window size
# include <sys/stat.h> // stat
# include <sys/types.h> // everything
# include <sys/acl.h> // acl_get_file acl_to_text
# include <sys/xattr.h> // listxattr
# include <uuid/uuid.h> // pwuid gid
# include <errno.h> // errno
# include <limits.h>
# include <time.h> // time
# include <dirent.h> // open dir
# include <pwd.h>
# include <grp.h>
# include <stdlib.h> // malloc
# include <unistd.h> // system calls
# include <stdio.h> // strerror
# include <string.h> // forbidden function #memset

//#include <libft.h>
//#include <ft_printf.h>

# define SIX_MONTH_SEC 15552000
# define IS_TOO_OLD(timespec) ((timespec) > SIX_MONTH_SEC)
# define IS_TOO_NEW(timespec) ((timespec) > SIX_MONTH_SEC)
# define DEFAULT "\e[0m"
# define LS_FLAGS "lRratuUGfh1"
# define CWD "."

typedef struct winsize	t_winsize;
typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_lst
{
	struct s_lst	*prev;
	struct s_lst	*next;
	void			*data;
}						t_lst;

typedef struct			s_cdir
{
	DIR		*cwd;
	t_lst	*cwd_file;
	char	*cur_path_name;
	size_t	cwd_nb_file;
}						t_cdir;

typedef struct			s_file
{
	t_dirent   		*file;
	t_stat	   		*file_stat;
	t_passwd   		*user; // ell
	t_group	   		*group; // ell
//	struct timespec	time;
	char	   		*path_file;
	char	   		human_time[16]; // ell
	char			sym_link[PATH_MAX]; //ell
	char			perm[12]; // ell
	int				acl; // ell
	int				xattr; / ell
}						t_file;

typedef struct			s_lsenv
{
	char	*pname;
	char	*color[13];
	t_lst	*arg;
	int		flag;
}						t_lsenv;

enum					e_flag
{
	ell = 1,
	recursive = 2,
	rever_sort = 4,
	show_all = 8,
	mtim = 16,
	atim = 32,
	ctim = 64,
	human_size = 128,
	no_sort = 256,
	one = 512,
	color = 1024
};

/*
** ls
*/
void					list_dir(char *path, t_lsenv *ls);

/*
** get_ arg / opt
*/
int						get_opt(int ac, char **av, char *known_flag);
char					*get_arg(int ac, char **av);
int						set_flag(int ac, char **av);

/*
** ripoff from ctime just for ls
*/
char					*time_format(time_t file_timespec, char *buf);

/*
** permission format
*/
void					perm_format(register mode_t st_mode, register char *restrict perm);

/*
** Merge sort
*/

/*
** lst
*/
t_lst					*init_lst__(void *data);
void					push_lst__(t_lst **node, void *data);
void					pop_lst__(t_lst **node, void (*del)());
void					append_lst__(t_lst *node, void *data);

#endif
