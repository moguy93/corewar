/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:08:31 by moguy             #+#    #+#             */
/*   Updated: 2020/02/17 08:02:57 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*new_lst(uint32_t id, uint32_t pc)
{
	t_process	*new;

	if (!(new = (t_process*)malloc(sizeof(t_process))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_process));
	new->r[0] = -(int32_t)id;
	new->pc = pc;
	return (new);
}

t_process	*push_lst(t_env *env, uint32_t id, uint32_t pc)
{
	t_process	*new;
	static int	rank = 2;

	if (!(new = new_lst(id, pc)))
		return (NULL);
	new->next = env->process;
	new->rank = rank;
	env->last_rank = (unsigned int)rank;
	env->process = new;
	env->process->tpc = env->process->pc;
	rank++;
	return (new);
}

t_process	*pop_lst(t_process *process, t_process *prev)
{
	t_process	*tmp;

	tmp = process;
	if (tmp->next)
	{
		process = process->next;
		if (prev)
			prev->next = process;
		ft_memdel((void**)&tmp);
		return (process);
	}
	ft_memdel((void**)&tmp);
	if (prev)
		prev->next = NULL;
	return (NULL);
}
