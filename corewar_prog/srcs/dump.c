/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 20:01:11 by moguy             #+#    #+#             */
/*   Updated: 2020/02/21 06:37:44 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char				hex_tab(uint8_t quartet)
{
	static char				hex_value[16] = {'0', '1', '2', '3', '4', '5', '6',
		'7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	return (hex_value[quartet]);
}

/*
** return the index of the dump arena.
*/

static inline char	hex_lines(int j)
{
	static uint8_t			nb[3] = {0};
	static char				buffer[9] = {'0', 'x', '0', '0', '0', '0',
		' ', ':', ' '};

	if (j == -1 && ft_memset(&nb[0], 0, 3) && ft_memset(&buffer[2], '0', 3))
		return (0);
	else if (j > 0)
	{
		if (j == 8)
			nb[2] += 4;
		return (buffer[j]);
	}
	if (nb[0] == 0 && nb[1] == 0 && nb[2] == 0)
		return (buffer[j]);
	if ((nb[2] % 16) == 0)
		nb[1]++;
	if ((nb[1] % 16) == 0 && (nb[2] % 16) == 0)
		nb[0]++;
	buffer[2] = hex_tab(nb[0] % 16);
	buffer[3] = hex_tab(nb[1] % 16);
	buffer[4] = hex_tab(nb[2] % 16);
	return (buffer[j]);
}

static inline void	print_octet(uint8_t hquartet, uint8_t lquartet, bool flush)
{
	static char				buffer[DUMP_LENGTH];
	static int				i = 0;
	static unsigned int		count = 0;
	int						j;

	if (count == 0 && (i += 9) && (j = -1))
		while (++j < 9)
			buffer[i - 9 + j] = hex_lines(j);
	buffer[i++] = hex_tab(hquartet);
	buffer[i++] = hex_tab(lquartet);
	count++;
	if (count == 64)
	{
		count = 0;
		buffer[i++] = ' ';
		buffer[i++] = '\n';
	}
	else
		buffer[i++] = ' ';
	if (flush)
	{
		i = 0;
		hex_lines(-1);
		write(1, &buffer[0], DUMP_LENGTH);
	}
}

void				dump(t_env *env)
{
	t_arena					*arena;
	unsigned int			i;

	i = 0;
	arena = &env->arena[0];
	buffer_cor(env->arg, -1, 1);
	while (i < MEM_SIZE - 1)
	{
		print_octet((arena[i].value >> 4) & 0xf, arena[i].value & 0xf, false);
		i++;
	}
	print_octet((arena[i].value >> 4) & 0xf, arena[i].value & 0xf, true);
	env->cycle_to_dump = env->opt[O_D];
}
