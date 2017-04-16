#include "ft_ls.h"

t_cdir	*init_dir__(char *path, t_lsenv *ls)
{
	t_cdir	*new_;

	errno = 0;
	if ((new_ = malloc(sizeof(t_cdir))) == NULL)
		return (NULL);
	memset(new_, 0, sizeof(t_cdir));
	if ((new_->cwd = opendir(path)) == NULL)
	{
		perror(ls->pname);
		free(new_);
		return (NULL);
	}
	if ((new_->cur_path = strdup(path)) == NULL)
	{
		perror(ls->pname);
		free(new_->cwd);
		free(new_);
		return (NULL);
	}
	new_->cwd_file = NULL;
	return (new_);
}
