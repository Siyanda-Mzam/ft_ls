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

#include "../includes/ft_ls.h"

void	add_to_record(t_reader *reader)
{
	//printf("In add record\n");
	t_list	*lst_alias;
	//t_list	*stat_lst_alias;
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
	char	*err_msg;
	if (!(reader->open.dirp = opendir(fname)))
	{
		err_msg = ft_strjoin("ft_ls: cannot access ", fname);
		perror(err_msg);
		exit(-1);
	}
	else
	{
		reader->store = ft_lstnew((void *)readdir(reader->open.dirp),
									sizeof(reader->open.read));
		lstat(fname, reader->buf);
	}
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
		else
			alpha_sort(reader, &a_to_z);
	}
}

void	just_display(char *fname, t_reader *reader)
{
	populate_list(fname, reader);
	display(reader);
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
