/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:24:20 by moguy             #+#    #+#             */
/*   Updated: 2020/02/27 17:08:31 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static inline char	hex_convert_char(unsigned int x, int unit)
{
	unsigned int	n;
	static char		hex_tab[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	n = x;
	if (unit > 0)
		n /= 16;
	if (unit > 1)
		n /= 16;
	if (unit > 2)
		n /= 16;
	n = n % 16;
	return (hex_tab[n]);
}

void				conv_hex(t_buf arg, char *buf, int *j)
{
	int				i;

	i = *j;
	buf[i] = '0';
	buf[i + 1] = 'x';
	buf[i + 2] = '0';
	buf[i + 3] = '0';
	buf[i + 4] = '0';
	buf[i + 5] = '0';
	if (arg.x > 0)
		buf[i + 5] = hex_convert_char(arg.x, 0);
	if (arg.x >= 16)
		buf[i + 4] = hex_convert_char(arg.x, 1);
	if (arg.x >= 256)
		buf[i + 3] = hex_convert_char(arg.x, 2);
	if (arg.x >= 4096)
		buf[i + 2] = hex_convert_char(arg.x, 3);
	i += 6;
	*j = i;
}

void				conv_str(t_buf arg, char *buf, int *j)
{
	int				i;
	int				k;

	k = 0;
	i = *j;
	while (arg.str[k])
	{
		buf[i] = arg.str[k];
		k++;
		i++;
	}
	*j = i;
}
