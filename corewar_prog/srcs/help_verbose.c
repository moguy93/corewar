/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_verbose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:23:11 by moguy             #+#    #+#             */
/*   Updated: 2020/02/27 16:59:19 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** wrtie a 'r' or not according to the function op_code and their arg number.
*/

static inline void	help_v2(t_env *env, t_process *p, uint32_t op, int i)
{
	if (((op == OP_LLDI || op == OP_LDI || op == OP_AND || op == OP_XOR
					|| op == OP_OR) && (i == 0 || i == 1)) || (op == OP_AFF
					&& i == 0) || (op == OP_STI && (i == 1 || i == 2)))
	{
		env->arg.n = p->r[p->instruct.args[i].arg - 1];
		buffer_cor(env->arg, 3, 0);
	}
	else if (op == OP_ST && i == 1)
	{
		env->arg.n = p->instruct.args[i].arg;
		buffer_cor(env->arg, 3, 0);
	}
	else
	{
		env->arg.str = "r";
		buffer_cor(env->arg, 0, 0);
		env->arg.n = p->instruct.args[i].arg;
		buffer_cor(env->arg, 3, 0);
	}
}

/*
** get the arg value according to the op op_codeand their arg number.
*/

void				help_verbose2(t_env *env, t_process *p, uint32_t op, int i)
{
	if (p->instruct.args[i].type == T_REG)
		help_v2(env, p, op, i);
	else if (p->instruct.args[i].type == T_IND)
	{
		if (((op == OP_LD || op == OP_LDI || op == OP_LLD || op == OP_LLDI)
					&& i == 0)
				|| ((op == OP_AND || op == OP_OR || op == OP_XOR)
					&& (i == 0 || i == 1))
				|| (op == OP_STI && i == 1))
		{
			env->arg.n = get_arg_value(env, p, i, (
							op == OP_LLDI || op == OP_LLD) ? 0 : 1);
			buffer_cor(env->arg, 3, 0);
		}
		else
		{
			env->arg.n = p->instruct.args[i].arg;
			buffer_cor(env->arg, 3, 0);
		}
	}
	else
	{
		env->arg.n = p->instruct.args[i].arg;
		buffer_cor(env->arg, 3, 0);
	}
}
