#include "ft_ls.h"

int		is_directory_we_want_to_list(const char *parent, char *name)
{
  struct stat st_buf;
  if (!strcmp(".", name) || !strcmp("..", name))
    return 0;
  char *path = alloca(strlen(name) + strlen(parent) + 2);
  sprintf(path, "%s/%s", parent, name);
  stat(path, &st_buf);
  return S_ISDIR(st_buf.st_mode);
}

void	recursive_list(const char *fname, int depth, t_reader *reader)
{
  reader->open.dirp = opendir(fname);
  //struct dirent *ent;
  while ((reader->open.read = readdir(reader->open.dirp)))
  {
    //char *entry_name = ent->d_name;
    printf("%s\n", reader->open.read->d_name);
    if (is_directory_we_want_to_list(fname, reader->open.read->d_name))
    {
      // You can consider using alloca instead.
      char *next = malloc(strlen(fname) + strlen(reader->open.read->d_name) + 2);
      sprintf(next, "%s/%s", fname, reader->open.read->d_name);
      recursive_list(next, depth + 1, reader);
      free(next);
    }
  }
 // closedir(reader->open.dirp);
}

