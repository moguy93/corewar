/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 03:13:07 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 03:13:43 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				free_env(t_env *env, char *arg)
{
	t_process		*tmp;

	tmp = NULL;
	if (arg)
		ft_strdel(&arg);
	if (env->process)
	{
		while (env->process->next)
		{
			tmp = env->process;
			env->process = env->process->next;
			ft_memdel((void**)&tmp);
		}
		ft_memdel((void**)&env->process);
	}
}
