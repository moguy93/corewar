/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:44:18 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:57:29 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** check if the register is valid and if the type of args given is corresponding
** to the op_code.
*/

bool				reg_is_valid(t_process *p, t_op_arg arg[MAX_ARGS_NUMBER])
{
	int			i;
	uint32_t	op;

	i = -1;
	op = p->instruct.op;
	while (++i < MAX_ARGS_NUMBER)
		if ((i < g_func_tab[op - 1].nb_arg && arg[i].type == 0)
				|| (arg[i].type == T_REG
				&& (arg[i].arg <= REG_NONE || arg[i].arg >= REG_MAX)))
			return (false);
	if (((op == OP_ST || op == OP_AFF || op == OP_STI) && arg[0].type != T_REG)
		|| ((op == OP_LD || op == OP_LLD) && arg[1].type != T_REG)
			|| ((op == OP_AND || op == OP_OR || op == OP_XOR || op == OP_LDI
						|| op == OP_LLDI) && arg[2].type != T_REG)
			|| ((op == OP_ADD || op == OP_SUB) && (arg[0].type != T_REG
						|| arg[1].type != T_REG || arg[2].type != T_REG))
			|| ((op == OP_LD || op == OP_LLD) && arg[0].type == T_REG)
			|| ((op == OP_LIVE || op == OP_ZJMP || op == OP_FORK
						|| op == OP_LFORK) && arg[0].type != T_DIR)
			|| (op == OP_ST && arg[1].type == T_DIR)
			|| ((op == OP_LDI || op == OP_LLDI) && arg[1].type == T_IND)
			|| (op == OP_STI && arg[2].type == T_IND))
		return (false);
	return (true);
}

/*
** get the value of a cell of the arena.
*/

int32_t				get_mem_cell(t_env *env, t_process *p, size_t siz)
{
	size_t		i;
	int32_t		val;
	uint8_t		tmp;
	bool		sign;

	i = 0;
	val = 0;
	sign = (bool)(env->arena[p->pctmp].value & MASK_NEG);
	while (i < siz)
	{
		val <<= 8;
		tmp = env->arena[p->pctmp].value;
		val |= (sign) ? (tmp ^ MASK_FF) : tmp;
		p->pctmp += 1;
		i++;
	}
	if (sign)
		val = ~(val);
	return (val);
}

/*
** get the value of the arg given if is type is register, indirect or direct.
*/

int32_t				get_arg_value(t_env *env, t_process *p, int i, bool mod)
{
	int32_t		value;
	int32_t		arg;

	arg = p->instruct.args[i].arg;
	if (p->instruct.args[i].type == T_DIR)
		value = arg;
	else if (p->instruct.args[i].type == T_REG)
		value = p->r[arg - 1];
	else
	{
		p->pctmp = p->pc + (uint32_t)((mod) ? (arg % IDX_MOD) : arg);
		value = get_mem_cell(env, p, REG_SIZE);
	}
	return (value);
}

/*
** get the arguments of an op, given by following the op_code and the encoding
** bytes in the arena, with get_mem_cell.
*/

static inline void	get_args(t_env *env, t_process *p, bool dir)
{
	int			i;

	i = 0;
	p->tpc++;
	while (i < g_func_tab[p->instruct.op - 1].nb_arg)
	{
		p->pctmp = p->tpc;
		if (p->instruct.args[i].type == T_DIR)
		{
			p->tpc = p->tpc + ((dir) ? 2 : 4);
			p->instruct.args[i].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
		}
		else if (p->instruct.args[i].type == T_IND)
		{
			p->tpc = p->tpc + 2;
			p->instruct.args[i].arg = get_mem_cell(env, p, 2);
		}
		else if (p->instruct.args[i].type == T_REG)
		{
			p->tpc += 1;
			p->instruct.args[i].arg = get_mem_cell(env, p, 1);
		}
		i++;
	}
}

/*
** get the args of an op without encoding byte and with an encoding byte.
*/

void				load_args(t_env *env, t_process *p, bool enco, bool dir)
{
	if (enco == false)
	{
		p->pctmp = p->tpc;
		p->tpc += (dir) ? 2 : 4;
		p->instruct.args[0].type = T_DIR;
		p->instruct.args[0].arg = get_mem_cell(env, p, (dir) ? 2 : 4);
	}
	else
		get_args(env, p, dir);
}
