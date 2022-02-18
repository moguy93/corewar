/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_pc_op_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 00:54:39 by moguy             #+#    #+#             */
/*   Updated: 2020/02/27 17:08:43 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	help_verbose_pc(t_env *env, t_process *p)
{
	env->arg.str = "ADV ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " (";
	buffer_cor(env->arg, 0, 0);
	env->arg.x = p->pc;
	buffer_cor(env->arg, 1, 0);
	env->arg.str = " -> ";
	buffer_cor(env->arg, 0, 0);
	env->arg.x = (p->tpc < p->pc) ? (4096 + p->tpc) : p->tpc;
	buffer_cor(env->arg, 1, 0);
	env->arg.str = ") ";
	buffer_cor(env->arg, 0, 0);
}

void				verbose_pc(t_env *env, t_process *p)
{
	int				i;

	i = -1;
	help_verbose_pc(env, p);
	p->pctmp = p->pc;
	while (++i < p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096))
	{
		env->arg.c = hex_tab((env->arena[p->pctmp].value >> 4) & 0xf);
		buffer_cor(env->arg, 4, 0);
		env->arg.c = hex_tab(env->arena[p->pctmp].value & 0xf);
		buffer_cor(env->arg, 4, 0);
		if (i + 1 < p->tpc - p->pc + ((p->tpc > p->pc) ? 0 : 4096))
			env->arg.str = " ";
		else
			env->arg.str = " \n";
		buffer_cor(env->arg, 0, 0);
		p->pctmp++;
	}
}

static inline void	help_v3(t_env *env, t_process *p, uint32_t op)
{
	if (op == OP_FORK || op == OP_LFORK)
	{
		env->arg.str = " (";
		buffer_cor(env->arg, 0, 0);
		if (op == OP_FORK)
			env->arg.n = p->pc + (p->instruct.args[0].arg % IDX_MOD);
		else
			env->arg.n = p->pc + p->instruct.args[0].arg;
		buffer_cor(env->arg, 3, 0);
		env->arg.str = ")";
		buffer_cor(env->arg, 0, 0);
	}
	else if (op == OP_ZJMP)
	{
		env->arg.str = (p->carry) ? " OK" : " FAILED";
		buffer_cor(env->arg, 0, 0);
	}
	env->arg.str = "\n";
	buffer_cor(env->arg, 0, 0);
}

void				help_verbose3(t_env *env, t_process *p, uint32_t op, int i)
{
	if (i + 1 < g_func_tab[op - 1].nb_arg)
	{
		env->arg.str = " ";
		buffer_cor(env->arg, 0, 0);
	}
	else
		help_v3(env, p, op);
}
