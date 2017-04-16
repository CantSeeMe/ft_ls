#include "ft_ls.h"

void	free_file(t_file *file)
{
	if (file->path_to_file)
	{
		free(file->name);
		free(file->path_to_file);
	}
	free(file->stat);
	free(file);
}

void	free_cdir(t_cdir *cdir)
{
	t_lst	*to_free;
	
	to_free = cdir->cwd_file;
	while (to_free)
		pop_lst__(&to_free, &free_file);
	free(cdir->cur_path);
	if (cdir->cwd)
		closedir(cdir->cwd);
	free(cdir);
}
