/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:13:25 by moguy             #+#    #+#             */
/*   Updated: 2020/02/14 02:13:40 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				op_fork(t_env *env, t_process *p)
{
	unsigned int	i;

	i = 0;
	p->pctmp = p->pc + (uint32_t)(p->instruct.args[0].arg % IDX_MOD);
	if (!(env->process = push_lst(env, (uint32_t)p->r[0], p->pctmp)))
	{
		error(LST_ERR, NULL, NULL);
		free_env(env, NULL);
		exit(EXIT_FAILURE);
	}
	env->process->alive = p->alive;
	env->process->carry = p->carry;
	while (i < REG_NUMBER)
	{
		env->process->r[i] = p->r[i];
		i++;
	}
}
