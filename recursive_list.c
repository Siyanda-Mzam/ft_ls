#include "ft_ls.h"

void	recursive_list(const char *fname, int depth, t_reader *reader)
{
	if (!(reader->open.dirp = opendir(fname)))
		return ;
	while ((reader->open.read = readdir(reader->open.dirp)))
	{
		if (reader->open.read->d_type == DT_DIR)
		{
			//fname = ft_strjoin(fname, reader->open.read->d_name);
			if (!(ft_strcmp(reader->open.read->d_name, ".") == 0 ||
					ft_strcmp(reader->open.read->d_name, "..") == 0))
				{
					fname = ft_strjoin(fname, "/");
					fname = ft_strjoin(fname, reader->open.read->d_name);
					fname = ft_strjoin(fname, "/");
					printf("%*s%s\n", depth * 2, "", reader->open.read->d_name);
					recursive_list(fname, depth + 1, reader);
				}
		}
		else
		{
			printf("%*s- %s\n", depth * 2, "", reader->open.read->d_name);
		}
		//closedir(reader->open.dirp);
	}
	//closedir(reader->open.dirp);
}
