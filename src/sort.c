/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomeirin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 13:25:28 by jomeirin          #+#    #+#             */
/*   Updated: 2016/06/17 13:25:32 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	to_lower(unsigned char *str)
{
	int i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) >= 65 && *(str + i) <= 90)
			*(str + i) = *(str + i) + 32;
		i++;
	}
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char*)ft_strcpy(ft_strnew(50), s1);
	str2 = (unsigned char*)ft_strcpy(ft_strnew(50), s2);
	to_lower(str1);
	to_lower(str2);
	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0') //If one string ends, this might segfault.
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i += 1;
	}
	free(str1);
	free(str2);
	return (0);
}

int		z_to_a(char *s1, char *s2)
{
	return (ft_strcmp(s1, s2) < 0);
}

int		a_to_z(char *s1, char *s2)
{
	return (ft_strcmp(s1, s2) > 0);
}



void	alpha_sort(t_reader *reader, int (*sort_by)(char *, char *))
{
	int		swap;
	t_list	*runner;
	void	*temp;
	char	*first;
	char	*second;

	swap = 1;
	while (swap == 1)
	{
		swap = 0;
		runner = reader->store;
		while (runner->next)
		{
			first = (char *)((struct dirent *)runner->content)->d_name;
			second = (char *)((struct dirent *)runner->next->content)->d_name;
			if ((sort_by)(first, second))
			{
				temp = runner->content;
				runner->content = runner->next->content;
				runner->next->content = temp;
				swap = 1;
			}
			runner = runner->next;
		}	
	}
}
