/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:13:03 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:13:15 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				sti(t_env *env, t_process *p)
{
	int32_t		val[3];

	val[0] = p->r[p->instruct.args[0].arg - 1];
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = get_arg_value(env, p, 2, true);
	p->pctmp = p->pc + ((val[1] + val[2]) % IDX_MOD);
	write_mem_cell(env, p, val[0]);
}
