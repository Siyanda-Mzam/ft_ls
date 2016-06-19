#include "ft_ls.h"

void	recursive_list(char *fname, int depth, t_reader *reader)
{
	//int			path_len;
	char		*path;
	char		*path_name;
	t_list		*runner;
	t_reader	*nreader;

	//path_len = 0;
	nreader = (t_reader *)malloc(sizeof(nreader));
	printf("\n%*s:\n", 10, fname);
	just_display(fname, reader);
	runner = reader->store->next;
	while (runner)
	{
		//if ((char)((struct dirent *)runner->content)->d_name[0] == '.')
		//	runner = runner->next;
		//else
		path_name= ft_strjoin("/", (char *)((struct dirent *)runner->content)->d_name);
		nreader->open.dirp = opendir(ft_strjoin(fname, path_name));
		if (!nreader->open.dirp)
			runner = runner->next;
		else 
		{
			path = ft_strjoin(fname, "/");
			path = ft_strjoin(path, (char *)((struct dirent *)(runner->content))->d_name);
			//populate_list(, reader);
			recursive_list(path, (depth + 1), nreader);
			runner = runner->next;
		}
	}
	//if (!(reader->open.read = readdir(reader->open.dirp)))
	//	return ;
/*	while ((reader->open.read = readdir(reader->open.dirp)))
	{
		if (reader->open.read->d_type == DT_DIR)
		{
			path = ft_strjoin(fname, reader->open.read->d_name);
			path_len = ft_strlen(path);
			path[path_len] = 0;
	}*/
}
