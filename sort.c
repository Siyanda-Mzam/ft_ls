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

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i += 1;
	}
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

	swap = 1;
	while (swap == 1)
	{
		swap = 0;
		runner = reader->store;
		while (runner->next)
		{
			if ((sort_by)(((struct dirent *)runner->content)->d_name,
				((struct dirent *)runner->next->content)->d_name))
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
