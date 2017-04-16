#include "ft_ls.h"

void	set_timespec(t_file *file, t_lsenv *ls)
{
	t_stat	*fstat;

	fstat = file->stat;
#ifdef __APPLE__
	if (ls->flag & ctim)
		file->time = &fstat->st_ctimespec;
	else if (ls->flag & atim)
		file->time = &fstat->st_atimespec;
	else
		file->time = &fstat->st_mtimespec;
#elif __linux__
	if (ls->flag & ctim)
		file->time = &fstat->st_ctim;
	else if (ls->flag & atim)
		file->time = &fstat->st_atim;
	else
		file->time = &fstat->st_mtim;
#endif
}
