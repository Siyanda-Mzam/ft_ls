#include "ft_ls.h"

size_t	ft_strlen(const char *s)
{
	int index;

	index = 0;
	while (s[index] != '\0')
	{
		index++;
	}
	return (index);
}

void	size_lstiter(t_list *lst)
{
	t_list	*runner;
	size_t	max;
	int		spaces;
	size_t	size;

	size = 0;
	spaces = 0;
	max = 0;
	runner = lst;
	while (runner)
	{
		size = ft_strlen((char *)runner->content);
		if (max < size)
			max = size;
		runner = runner->next;
	}
	runner = lst;
	while (runner)
	{
		runner->size = ft_strlen((char *)runner->content);
		spaces = max - runner->size;
		while (spaces > 0)
		{
			*(char *)(runner->content + runner->size + spaces) = ' ';
			spaces--;
		}
		runner = runner->next;
	}
}

void	display(t_reader *reader)
{
	t_list *runner;

	runner = reader->store->next;
	//size_lstiter(runner);
	while (runner)
	{
		printf("%s    \t", ((struct dirent *)runner->content)->d_name);
		runner = runner->next;
	}
	printf("\n");
}
