/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:07:20 by vrenaudi          #+#    #+#             */
/*   Updated: 2019/03/07 14:55:48 by vrenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

static void		init_env(t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->nb_ants = -1;
	env->start_index = -1;
	env->end_index = -1;
}

int				main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	if (argc > 1)
		analyze_options(&env, argv[1]);
	read_data(&env);
	get_connexion_start_end(&env);
	analyze_graph(&env);
	print_data(env.data, env.nb_line);
	fill_combinations(&env);
	dispatch_ants(&env);
	print_option(&env);
	free_memory(&env);
	return (0);
}
