/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 22:18:40 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:08:41 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** stock a big string for error purpose.
*/

char	*singleton_str(int error)
{
	static char		magic[4][150];

	if (magic[0][0] == 0)
	{
		ft_strcpy(&magic[0][0], "Magic number defined in the header of one of t\
he file is invalid. Magic number has to be COREWAR_EXEC_MAGIC");
		ft_strcpy(&magic[1][0], "The size defined in the header of one of the \
file is invalid. Size can't be more than CHAMP_MAX_SIZE.");
		ft_strcpy(&magic[2][0], "The size of the redcode is too long, or \
different than the size defined in the header.");
		ft_strcpy(&magic[3][0], "Too many players, only 4 contestants can \
fight in the area at once, for a minimum of one.");
	}
	return (&magic[error][0]);
}

/*
** verify if the player's id are between 1 and number of players.
*/

int		check_too_high_id(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_pl)
	{
		if (env->player[i].id > env->nb_pl || env->player[i].id < 1)
			return (1);
		i++;
	}
	return (0);
}

/*
** get the dump's value.
*/

int		get_dump(char *arg, unsigned int *j)
{
	unsigned int	i;
	long long int	dump;

	i = *j + 2;
	i = after_space(arg, i);
	if (!ft_isdigit(arg[i]) || (dump = ft_atoi(&arg[i])) < 1 || dump > INT_MAX)
		return (-1);
	while (ft_isdigit(arg[i]))
		i++;
	if (!ft_is_whitespace(arg[i]))
		return (-1);
	*j = i;
	return ((int)dump);
}
