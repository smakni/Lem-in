/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_second.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smakni <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:33:26 by smakni            #+#    #+#             */
/*   Updated: 2019/03/07 10:58:44 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static void	check_nb_path(t_env *env, char **flow)
{
	int i;

	i = 0;
	while (i < env->nb_nodes)
	{
		if (flow[env->start_index][i] == 1)
			env->nb_path++;
		i++;
	}
}

static void	reduce_len_paths(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_path)
	{
		env->paths[i].len--;
		i++;
	}
}

void		bfs_second(t_env *env, char **flow)
{
	if (!flow)
		return ;
	check_nb_path(env, flow);
	if (!(env->paths = ft_memalloc(sizeof(t_path) * env->nb_path)))
		exit(-1);
	env->nb_fifo = env->nb_path;
	if (init_paths_second(env) == -1)
		exit(-1);
	if (!(env->fifo = ft_memalloc(sizeof(t_fifo) * env->nb_nodes)))
		exit(-1);
	fill_initial_fifo_second(env, flow);
	if (while_fifo_second(env, flow) == -1)
		exit(-1);
	reduce_len_paths(env);
}
