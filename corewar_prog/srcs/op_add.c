/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:08:10 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:08:23 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				add(t_env *env, t_process *p)
{
	int32_t		val[3];

	(void)env;
	val[0] = p->r[p->instruct.args[0].arg - 1];
	val[1] = p->r[p->instruct.args[1].arg - 1];
	val[2] = p->instruct.args[2].arg;
	p->r[val[2] - 1] = val[0] + val[1];
	p->carry = (p->r[val[2] - 1]) ? false : true;
}
