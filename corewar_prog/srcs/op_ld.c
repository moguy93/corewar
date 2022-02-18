/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:07:08 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:07:23 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				ld(t_env *env, t_process *p)
{
	int32_t		value;

	value = get_arg_value(env, p, 0, true);
	p->r[p->instruct.args[1].arg - 1] = value;
	if (value)
		p->carry = false;
	else
		p->carry = true;
}
