/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:15:23 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:12:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool			encoding_byte_pres(char type)
{
	static bool bytes[NB_OPS] = {1, 1, 1, 0, 0, 1, 1, 1,
									1, 0, 1, 1, 1, 1, 1, 0};

	return (bytes[(int)type]);
}

unsigned char	encoding_byte(unsigned char byte, unsigned int param, int type)
{
	static int		pow[6] = {128, 64, 32, 16, 8, 4};

	if (type == TOK_REG)
		byte += pow[(param * 2) + 1];
	else if (type == TOK_NUMBER)
	{
		byte += pow[(param * 2)];
		byte += pow[(param * 2) + 1];
	}
	else if (type == TOK_LNUMBER)
		byte += pow[(param * 2)];
	return (byte);
}
