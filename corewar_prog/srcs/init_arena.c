/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 02:25:29 by moguy             #+#    #+#             */
/*   Updated: 2020/02/17 05:27:32 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					init_arena(t_env *env)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	offset;

	i = 0;
	env->cycle_to_dump = (int)env->opt[O_D];
	offset = MEM_SIZE / env->nb_pl;
	while (i < env->nb_pl)
	{
		j = 0;
		while (j < env->player[i].size)
		{
			env->arena[offset * i + j].value = (uint8_t)env->player[i].champ[j];
			env->arena[offset * i + j].id = (short)env->player[i].id;
			j++;
		}
		if (create_pro(env, i, offset * i))
			return (1);
		i++;
	}
	return (0);
}
