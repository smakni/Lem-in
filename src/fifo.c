/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:19:07 by smakni            #+#    #+#             */
/*   Updated: 2019/03/06 17:20:31 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static t_fifo	get_tmp_info(t_fifo fifo)
{
	t_fifo	tmp;

	tmp.index = fifo.index;
	tmp.path_index = fifo.path_index;
	tmp.from = fifo.from;
	return (tmp);
}

static int		dequeue_one_fifo(t_env *env)
{
	int		i;
	int		j;
	int		len;
	t_fifo	tmp;

	i = 1;
	j = 0;
	tmp = get_tmp_info(env->fifo[0]);
	len = env->paths[tmp.path_index].len;
	while (i < env->nb_fifo)
		env->fifo[j++] = env->fifo[i++];
	env->nb_fifo--;
	env->paths[tmp.path_index].len++;
	env->paths[tmp.path_index].path[len] = tmp.index;
	if (tmp.index == env->end_index)
	{
		env->paths[tmp.path_index].end_found = 1;
		return (1);
	}
	if (env->rooms[tmp.index].capacity == 1 && tmp.from == 0)
		env->flow_to_find = -1;
	else
		env->flow_to_find = 0;
	return (0);
}

static void		enqueue_fifo(t_env *env, int i, int *nb_path_needed, t_fifo tmp)
{
	env->fifo[env->nb_fifo].index = i;
	env->fifo[env->nb_fifo].from = tmp.from;
	if (i != env->end_index)
		env->rooms[i].check = 1;
	if (*nb_path_needed == 0)
	{
		env->fifo[env->nb_fifo].path_index = tmp.path_index;
		(*nb_path_needed)++;
	}
	else
	{
		add_path(env->paths, env->nb_path, tmp.path_index, env->nb_nodes);
		env->fifo[env->nb_fifo].path_index = env->nb_path++;
	}
	env->nb_fifo++;
}

static void		choose_flow(t_env *env, t_fifo tmp, int i, int *nb_path_needed)
{
	if (env->flow_to_find == -1)
	{
		if (env->matrice[tmp.index][i] == 1 && env->rooms[i].check == 0
				&& env->flow[tmp.index][i] == -1)
		{
			tmp.from = -1;
			enqueue_fifo(env, i, nb_path_needed, tmp);
		}
	}
	else if (env->flow_to_find == 0)
	{
		if (env->matrice[tmp.index][i] == 1 && env->rooms[i].check == 0
			&& (env->flow[tmp.index][i] == -1 || env->flow[tmp.index][i] == 0))
		{
			tmp.from = env->flow[tmp.index][i];
			enqueue_fifo(env, i, nb_path_needed, tmp);
		}
	}
}

int				while_fifo(t_env *env)
{
	int		i;
	int		nb_path_needed;
	t_fifo	tmp;

	env->flow_to_find = 0;
	while (env->nb_fifo != 0)
	{
		tmp = env->fifo[0];
		if (dequeue_one_fifo(env) == 1)
			break ;
		i = -1;
		nb_path_needed = 0;
		while (++i < env->nb_nodes)
			choose_flow(env, tmp, i, &nb_path_needed);
	}
	return (0);
}
