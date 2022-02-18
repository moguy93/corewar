/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:18:42 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:18:59 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				reverse_bits(char buff[LBE_BUFFER], int num)
{
	int		swapped;

	swapped = ((num >> 24) & 0xff) |
		((num << 8) & 0xff0000) |
		(int)((num >> 8) & 0xff00) |
		(int)((num << 24) & (int)0xff000000);
	ft_memcpy(&buff[0], &swapped, sizeof(int));
}

unsigned char		rev_bits(unsigned char b, bool shift)
{
	b = (unsigned char)((b & 0xF0) >> 4 | (b & 0x0F) << 4);
	b = (unsigned char)((b & 0xCC) >> 2 | (b & 0x33) << 2);
	b = (unsigned char)((b & 0xAA) >> 1 | (b & 0x55) << 1);
	if (shift)
		b = (unsigned char)(b << 2);
	return (b);
}
