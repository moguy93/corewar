/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:12:28 by moguy             #+#    #+#             */
/*   Updated: 2020/02/18 06:47:04 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zjmp(t_env *env, t_process *p)
{
	int16_t	value;

	value = (int16_t)get_arg_value(env, p, 0, true);
	if (p->carry)
		p->tpc = p->pc + (value % IDX_MOD);
}
