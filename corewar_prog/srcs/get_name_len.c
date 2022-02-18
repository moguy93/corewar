/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 20:52:49 by moguy             #+#    #+#             */
/*   Updated: 2019/10/13 17:28:25 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int		get_name_len(char *name)
{
	unsigned int	len;

	len = 0;
	if (!name)
		return (0);
	while (name[len] && !ft_is_whitespace(name[len]))
		len++;
	return (len);
}
