/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:44:36 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/03/06 18:21:51 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int		*dup_table(int *src, int len)
{
	int		*dst;

	if (!(dst = ft_memalloc(sizeof(int) * len)))
		return (NULL);
	ft_memcpy(dst, src, len * sizeof(int));
	return (dst);
}

int		*expand_table(int *src, int len, int to_add)
{
	int		*dst;

	if (!(dst = ft_memalloc(sizeof(int) * (len + 1))))
		return (NULL);
	if (src)
	{
		ft_memcpy(dst, src, len * sizeof(int));
		free(src);
	}
	dst[len] = to_add;
	return (dst);
}

void	add_path(t_path *tocpy, int nb_path, int ptocpy, int len)
{
	tocpy[nb_path].path = dup_table(tocpy[ptocpy].path, len);
	tocpy[nb_path].len = tocpy[ptocpy].len;
}

char	**increase_size(char **data, char *line, int *re, int *nb_line)
{
	char	**tmp;
	int		i;
	int		size;

	tmp = NULL;
	(*re)++;
	size = NB_LINE * (*re) + 1;
	if (!(tmp = ft_memalloc(sizeof(char *) * size)))
		exit(-1);
	i = 0;
	while (i < (*nb_line))
	{
		tmp[i] = data[i];
		i++;
	}
	tmp[i] = line;
	free(data);
	(*nb_line)++;
	return (tmp);
}
