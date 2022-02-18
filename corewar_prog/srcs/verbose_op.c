/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 07:08:48 by moguy             #+#    #+#             */
/*   Updated: 2020/02/20 05:14:53 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline void	help_vop2(t_env *env, t_process *p, int32_t arg)
{
	arg = (get_arg_value(env, p, 1, true) + get_arg_value(env, p, 2, true));
	env->arg.str = "       | -> store to ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = get_arg_value(env, p, 1, true);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " + ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = get_arg_value(env, p, 2, true);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " = ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = arg;
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " (with pc and mod ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = p->pc + (arg % IDX_MOD);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = ")\n";
	buffer_cor(env->arg, 0, 0);
}

static inline void	help_vop(t_env *env, t_process *p, int32_t arg)
{
	arg = (get_arg_value(env, p, 0, true) + get_arg_value(env, p, 1, true));
	env->arg.str = "       | -> load from ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = get_arg_value(env, p, 0, true);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " + ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = get_arg_value(env, p, 1, true);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " = ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = arg;
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " (with pc ";
	buffer_cor(env->arg, 0, 0);
	if (p->instruct.op == OP_LDI)
	{
		env->arg.str = "and mod ";
		buffer_cor(env->arg, 0, 0);
	}
	env->arg.n = p->pc + ((p->instruct.op == OP_LDI) ? (arg % IDX_MOD) : arg);
	buffer_cor(env->arg, 3, 0);
	env->arg.str = ")\n";
	buffer_cor(env->arg, 0, 0);
}

void				help_verbose_op(t_env *env, t_process *p, uint32_t op)
{
	int				i;
	int32_t			arg;

	i = -1;
	arg = 0;
	while (++i < g_func_tab[op - 1].nb_arg)
	{
		help_verbose2(env, p, op, i);
		help_verbose3(env, p, op, i);
	}
	if (p->instruct.op == OP_LDI || p->instruct.op == OP_LLDI)
		help_vop(env, p, arg);
	else if (p->instruct.op == OP_STI)
		help_vop2(env, p, arg);
}

void				verbose_op(t_env *env, t_process *p)
{
	int				i;
	uint32_t		op;

	i = p->rank;
	op = p->instruct.op;
	if (op == OP_AFF)
		return ;
	if (i < 10)
		env->arg.str = "P    ";
	else if (i >= 10 && i < 100)
		env->arg.str = "P   ";
	else if (i >= 100 && i < 1000)
		env->arg.str = "P  ";
	else
		env->arg.str = "P ";
	buffer_cor(env->arg, 0, 0);
	env->arg.n = i;
	buffer_cor(env->arg, 3, 0);
	env->arg.str = " | ";
	buffer_cor(env->arg, 0, 0);
	env->arg.str = g_func_tab[p->instruct.op - 1].name;
	buffer_cor(env->arg, 0, 0);
	env->arg.str = " ";
	buffer_cor(env->arg, 0, 0);
	help_verbose_op(env, p, op);
}
