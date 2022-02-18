/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:21:28 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 06:30:03 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int		after_space(char *arg, unsigned int i)
{
	if (!arg)
		return (0);
	while (arg[i] && ft_is_whitespace(arg[i]))
		i++;
	return (i);
}
