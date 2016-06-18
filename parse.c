/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 13:24:36 by jomeirin          #+#    #+#             */
/*   Updated: 2016/06/17 15:47:00 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*ft_lstnew(void const *content, size_t size)
{
	t_list	*new_list;

	if (!(new_list = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content && size > 0)
	{
		if(!(new_list->content = malloc(size)))
		{
			free(new_list);
			return (NULL);
		}
		memcpy(new_list->content, content, size);
		new_list->content_size = size;
	}
	else
	{
		new_list->content = NULL;
		new_list->content_size = 0;
	}
	new_list->next = NULL;
	return (new_list);
}

void	add_to_record(t_reader *reader)
{
	//printf("In add record\n");
	t_list *lst_alias;
	//printf("Adding to record in the beginning: %s\n", reader->open.read->d_name);
	if (!reader->store->next)
	{
		reader->store->next = ft_lstnew(reader->open.read,
									sizeof(reader->store->next) * STD_SIZ);
	}
	else
	{
		lst_alias = reader->store;
		while(lst_alias->next)
			lst_alias = lst_alias->next;
		lst_alias->next = ft_lstnew(reader->open.read,
									sizeof(reader->store->next) * STD_SIZ);
	}
}

int		init(char *fname, t_reader *reader)
{
	if (!(reader->open.dirp = opendir(fname)))
	{
		perror("ft_ls: cannot access ");
		return (-1);
	}
	else
		reader->store = ft_lstnew((void *)readdir(reader->open.dirp),
									sizeof(reader->open.read));
	return (1);
}

void	populate_list(char *fname, t_reader *reader)
{
	if (init(fname, reader) == -1)
		return ;
	else
	{
		while ((reader->open.read = readdir(reader->open.dirp)))
			if (reader->open.read->d_name[0] != '.')
				add_to_record(reader);
		if (reader->flags.reverse == 'r')
			alpha_sort(reader, &z_to_a);
		else alpha_sort(reader, &a_to_z);
	}
}
//TODO: Need an extra method here for error handling.
void	just_display(char *fname, t_reader *reader)
{
	populate_list(fname, reader);
	display(reader);
}

void	find_flags(int argc, char **argv, t_flags *flags)
{
	int i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'R')
		{
			flags->recursive = 'R';
			i++;
		}
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'l')
		{
			flags->long_list = 'l';
			i++;
		}
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'r')
		{
			flags->reverse = 'r';
			i++;
		}
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == 't')
		{
			flags->time = 't';
			i++;
		}
		if (argv[i] && argv[i][0] == '-' && argv[i][1] == 'a')
		{
			flags->all = 'a';
			i++;
		}
		i++;
	}
}

void	init_flags(t_flags *flags)
{
	flags->recursive = '\0';
	flags->long_list = '\0';
	flags->reverse = '\0';
	flags->time = '\0';
	flags->all = '\0';
}
//void	display_flags(t_flags flags, t_reader reader)
//{
	
//}
//void	reursive_print(t_flags flags, t_reader reader)

void	apply_flags(char *fname, t_reader *reader)
{
	if (reader->flags.recursive == 'R')
	{
		recursive_list(fname, 0, reader);
		printf("recursive");//recursive_print(reader);
	}
}

void	parse(int argc, char **argv, t_reader *reader)
{
	char			*dot;
	//static int		depth;
	//t_flags	flags;

	dot = ".\0";
	init_flags(&(reader->flags));
	if (argc == 1)
		just_display(dot, reader);
	else if (argc == 2 && argv[1][0] != '-')
			just_display(argv[1], reader);
	else
	{
		//TODO: This is where things get really interesting. Need to search for
		// flags, parse them and collect data relevant to each.
		if (argv[1][0] == '-')
		{
			if (argv[argc - 1][0] == '-')				
			{
				find_flags(argc, argv, &(reader->flags));
				if (init(dot, reader) == -1)
					return ;
				//find_flags(argc, argv, &(reader->flags));
				//just_display(".\0", reader);
				//populate_list(dot, reader);
				apply_flags(dot, reader);
			}
			else if (init(argv[argc - 1], reader) != -1)
			{
				find_flags(argc, argv, &(reader->flags));
				//populate_list(argv[argc - 1], reader);
				//just_display(argv[argc - 1], reader);
				apply_flags(argv[argc - 1], reader);
			}
			//display_flags(flags, reader);
		}
		  
		printf("%c:\n", reader->flags.recursive);
		printf("%c:\n", reader->flags.reverse);
		printf("Fucks\n");
	}
	closedir(reader->open.dirp);
}
