/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:14:13 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:14:34 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				lldi(t_env *env, t_process *p)
{
	int32_t		val[3];

	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->pctmp = p->pc + (uint32_t)(val[0] + val[1]);
	p->r[val[2] - 1] = get_mem_cell(env, p, REG_SIZE);
	p->carry = (p->r[val[2] - 1]) ? false : true;
}
