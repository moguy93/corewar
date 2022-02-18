/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:11:24 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:11:41 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		xor(t_env *env, t_process *p)
{
	int32_t		val[3];

	val[0] = get_arg_value(env, p, 0, true);
	val[1] = get_arg_value(env, p, 1, true);
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] ^ val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}
