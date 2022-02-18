/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:16:03 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 07:04:17 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char				*merge_args(int ac, char **av)
{
	char			*tmp;
	char			*tmp2;
	int				i;

	i = 1;
	if (!(tmp = ft_strdup(av[i])))
		return (NULL);
	while (++i < ac)
	{
		if (!(tmp2 = ft_strjoin(tmp, " ")))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		ft_strdel(&tmp);
		if (!(tmp = ft_strjoin(tmp2, av[i])))
		{
			ft_strdel(&tmp2);
			return (NULL);
		}
		ft_strdel(&tmp2);
	}
	return (tmp);
}
