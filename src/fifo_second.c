/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo_second.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:19:07 by smakni            #+#    #+#             */
/*   Updated: 2019/03/06 16:26:28 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static	void	dequeue_one_fifo(t_env *env)
{
	int		i;
	int		j;
	int		len;
	int		tmp_index;
	int		tmp_i_p;

	i = 1;
	j = 0;
	tmp_index = env->fifo[0].index;
	tmp_i_p = env->fifo[0].path_index;
	len = env->paths[tmp_i_p].len;
	while (i < env->nb_fifo)
		env->fifo[j++] = env->fifo[i++];
	if (env->paths[tmp_i_p].end_found == 0)
	{
		env->paths[tmp_i_p].len++;
		env->paths[tmp_i_p].path[len] = tmp_index;
		if (tmp_index == env->end_index)
			env->paths[tmp_i_p].end_found = 1;
	}
	env->nb_fifo--;
}

static	int		enqueue_fifo(t_env *env, int i, t_fifo tmp)
{
	env->fifo[env->nb_fifo].index = i;
	if (i != env->end_index)
		env->rooms[i].check = 1;
	env->fifo[env->nb_fifo].path_index = tmp.path_index;
	env->nb_fifo++;
	return (0);
}

int				while_fifo_second(t_env *env, char **flow)
{
	int		i;
	t_fifo	tmp;

	while (env->nb_fifo != 0)
	{
		tmp = env->fifo[0];
		dequeue_one_fifo(env);
		i = 0;
		while (i < env->nb_nodes)
		{
			if (flow[tmp.index][i] == 1 && env->rooms[i].check == 0)
			{
				if (enqueue_fifo(env, i, tmp) == -1)
					return (-1);
			}
			i++;
		}
	}
	return (0);
}
