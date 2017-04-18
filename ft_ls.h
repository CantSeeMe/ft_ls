/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:04:26 by jye               #+#    #+#             */
/*   Updated: 2017/04/18 02:24:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <errno.h>
# include <limits.h>
# include <time.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

//#include <libft.h>
//#include <ft_printf.h>

# define SIX_MONTH_SEC 15552000
# define IS_TOO_OLD(timespec) ((timespec) > SIX_MONTH_SEC)
# define IS_TOO_NEW(timespec) ((timespec) > SIX_MONTH_SEC)
# define TIME_FLAG (ctim | atim | mtim)
//# define DEFAULT "\e[0m"
# define LS_FLAGS "lRratuUGfh1"
# define CWD "."
# define MIN_WIDTH 1

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
	DIR			*cwd;
	t_lst		*cwd_file;
	char		*cur_path;
	size_t		cwd_nb_file;
	size_t		max_len;
	int			errno_;
}						t_cdir;

typedef struct			s_file
{
//	t_dirent   		*file;
	t_stat	   		stat;
//	char			*group_name; // strdup if NULL show gid
//	char			*user_name; // strdup, if NULL show uid
	struct timespec	*time; // which st_*tim to use;
	char			*name;
	char	   		*path_to_file;
//	char	   		human_time[16];
	char			sym_link[PATH_MAX];
//	char			perm[12];
	int				acl;
	int				xattr;
}						t_file;

typedef struct			s_lsenv
{
	char		*pname;
//	char		*color[11];
	t_lst		*file;
	t_lst		*dir;
	t_winsize	winsize;
	int			flag;
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
	color = 1024,
	show_folder = 2048
};

/*
** ls
*/
void					set_ls_args(t_lsenv *ls, int ac, char **av);
void					list_dir(t_lsenv *ls);
void					list_args(t_lsenv *ls);

/*
** additional bullshit because of norm ¯\_(ツ)_/¯
*/
void					set_timespec(t_file *file, t_lsenv *ls);

/*
** init struct
*/
t_file					*init_file__(t_cdir *cdir,
									t_dirent *cfile,
									t_lsenv *ls);
t_cdir					*init_dir__(char *path, t_lsenv *ls);
int						init_fstat__(t_file *file_data);


/*
** get_ arg / opt
*/
int						get_opt(int ac, char **av, char *known_flag);
char					*get_arg(int ac, char **av);
int						set_flag(int ac, char **av);

/*
** sort int / ascii using merge
*/
t_lst					*sort_int(t_lst **stack, size_t slen);
t_lst					*sort_ascii(t_lst **stack, size_t slen);

/*
** print_list / ell / one
*/
void					print_list(t_cdir *cdir, t_lsenv *ls);

/*
** ripoff from ctime just for ls
*/
char					*time_format(time_t file_timespec);

/*
** permission format
*/
void					perm_format(register mode_t st_mode, register char *restrict perm);

/*
** free custom struct
*/
void					free_file(t_file *file);
void					free_cdir(t_cdir *cdir);

/*
** lst
*/
t_lst					*init_lst__(void *data);
void					push_lst__(t_lst **node, void *data);
void					pop_lst__(t_lst **node, void (*del)());
void					append_lst__(t_lst *node, void *data);

#endif
