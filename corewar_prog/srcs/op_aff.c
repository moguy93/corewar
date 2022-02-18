/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:15:54 by moguy             #+#    #+#             */
/*   Updated: 2020/02/20 05:59:57 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				aff(t_env *env, t_process *p)
{
	static char		str[8] = "Aff:  \n";

	if (!env->opt[O_A])
		return ;
	str[5] = (char)(p->r[p->instruct.args[0].arg - 1] % 256);
	env->arg.str = &str[0];
	buffer_cor(env->arg, 0, 0);
}
