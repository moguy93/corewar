/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:07:45 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:08:02 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				st(t_env *env, t_process *p)
{
	int32_t		value;
	int32_t		tmp;

	value = p->r[p->instruct.args[0].arg - 1];
	tmp = p->instruct.args[1].arg;
	if (p->instruct.args[1].type == T_REG)
		p->r[tmp - 1] = value;
	else if (p->instruct.args[1].type == T_IND)
	{
		p->pctmp = p->pc + (tmp % IDX_MOD);
		write_mem_cell(env, p, value);
	}
}
