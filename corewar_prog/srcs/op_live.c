/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:06:39 by moguy             #+#    #+#             */
/*   Updated: 2020/03/01 20:16:08 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				live(t_env *env, t_process *p)
{
	int32_t			value;

	env->curr_lives++;
	value = -(get_arg_value(env, p, 0, true));
	p->alive = env->cycle_tot + env->cycle_curr;
	if (value < 1 || value > (int32_t)env->nb_pl)
		return ;
	env->live_pl[value - 1]++;
	env->last_live = (uint32_t)value;
	env->last_cycle_lived = p->alive;
	env->last_cycle_live[value - 1] = p->alive;
	env->arena[p->pc].living = 50;
	env->arena[p->pc].living_id = value;
	if (!(env->opt[O_V] & (1 << 0)))
		return ;
	env->arg.str = "Player ";
	buffer_cor(env->arg, 0, 0);
	env->arg.u = env->player[value - 1].id;
	buffer_cor(env->arg, 2, 0);
	env->arg.str = " (";
	buffer_cor(env->arg, 0, 0);
	env->arg.str = &env->player[value - 1].name[0];
	buffer_cor(env->arg, 0, 0);
	env->arg.str = ") is said to be alive\n";
	buffer_cor(env->arg, 0, 0);
}
