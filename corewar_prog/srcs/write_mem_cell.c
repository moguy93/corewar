/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_mem_cell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:10:31 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:12:53 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** writes in the arena.
*/

void		write_mem_cell(t_env *env, t_process *p, int32_t value)
{
	int			i;
	uint8_t		val;

	i = 0;
	while (i < REG_SIZE)
	{
		val = (uint8_t)((value << (8 * i)) >> (8 * (sizeof(int) - 1)));
		env->arena[p->pctmp].value = val;
		if (-(p->r[0]) > 0 && -(p->r[0]) <= (short)env->nb_pl)
			env->arena[p->pctmp].id = (short)p->r[0];
		env->arena[p->pctmp].recent = 50;
		p->pctmp++;
		i++;
	}
}
