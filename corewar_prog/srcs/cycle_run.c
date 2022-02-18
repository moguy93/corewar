/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 07:15:39 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 04:52:19 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** show the current cycle.
*/

static inline void	help_cycle_run(t_env *env)
{
	env->arg.str = "It is now cycle ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = env->cycle_tot + env->cycle_curr;
	buffer_cor(env->arg, 3, 0);
	env->arg.str = "\n";
	buffer_cor(env->arg, 0, 0);
}

/*
** execute one cycle for each process alive.
*/

int					cycle_run(t_env *env, t_process *p)
{
	t_process		*tmp;

	tmp = p;
	env->cycle_curr++;
	if (env->opt[O_V] & (1 << 1))
		help_cycle_run(env);
	while (tmp)
	{
		if ((tmp->cycle_to_exec - 1) == 0)
			launch_instruct(env, tmp);
		if (--tmp->cycle_to_exec < 0)
		{
			ft_memset(&tmp->instruct, 0, sizeof(t_instruct));
			create_instruct(env, tmp);
			tmp->cycle_to_exec--;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
	return (1);
}
