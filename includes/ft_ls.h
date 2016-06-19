/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 13:25:48 by jomeirin          #+#    #+#             */
/*   Updated: 2016/06/17 15:47:04 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H
#define CURRENT_DIR '.'
#define HIDDEN CURRENT_DIR
#define STD_SIZ 4
#define ASCENDING a
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef struct		s_flags
{
	char			recursive;
	char			long_list;
	char			reverse;
	char			time;
	char			all;
}					t_flags;

typedef struct		s_dir_files_opener
{
	DIR				*dirp;
	struct dirent	*read;
}					t_opener;

typedef struct		s_dir_files_reader
{
	t_opener		open;
	t_list			*store;
	t_flags			flags;
	struct stat		*buf;
}					t_reader;

void				parse(int argc, char **argv, t_reader *reader);
void				just_display(char *fname, t_reader *reader);
void				sort(t_reader *reader);
int					z_to_a(char *s1, char *s2);
int					a_to_z(char *s1, char *s2);
void				alpha_sort(t_reader *reader, int (*cmp)(char *, char *));
void				init_flags(t_flags *flags);
void				find_flags(int argc, char **argv, t_flags *flags);
void				apply_flags(char *fname, t_reader *reader);
void				display(t_reader *reader);
void				recursive_list(char *fname, int depth, t_reader *reader);
#endif
