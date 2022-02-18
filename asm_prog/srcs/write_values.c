/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:35:34 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 20:37:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline short	get_label_pos(t_env *env, int label)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = -1;
	if (label == -1)
		return (-1);
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_LABEL)
			j++;
		if (j == label)
			return ((short)env->lexemes[i].start_byte);
		i++;
	}
	return (-1);
}

static void			write_label(t_env *env, int fd, t_lexem lex, int param)
{
	int		val;
	short	addr;

	if (g_direct_size[(int)lex.opcode] == IND_SIZE)
	{
		addr = get_label_pos(env, lex.label[param]) - (short)lex.start_byte;
		swap_short_bytes(&addr);
		write(fd, &addr, IND_SIZE);
	}
	else
	{
		val = get_label_pos(env, lex.label[param]);
		val -= (unsigned short)lex.start_byte;
		val = reverse_int_bytes(val);
		write(fd, &val, DIR_SIZE);
	}
}

void				write_indirect_number(t_env *env, int fd, t_lexem lex,
																	int param)
{
	short	val;

	if (lex.label[param] >= 0)
	{
		val = get_label_pos(env, lex.label[param]);
		val -= (unsigned short)lex.start_byte;
	}
	else
		val = (short)lex.args[param].nb;
	swap_short_bytes(&val);
	write(fd, &val, IND_SIZE);
}

void				write_direct_number(t_env *env, int fd, t_lexem lex,
																	int param)
{
	int		val;
	short	addr;

	if (lex.label[param] >= 0)
		write_label(env, fd, lex, param);
	else if (g_direct_size[(int)lex.opcode] == DIR_SIZE)
	{
		val = reverse_int_bytes((int)lex.args[param].nb);
		write(fd, &val, DIR_SIZE);
	}
	else
	{
		addr = (short)lex.args[param].nb;
		swap_short_bytes(&addr);
		write(fd, &addr, IND_SIZE);
	}
}

void				write_register(int fd, t_lexem lex, int param)
{
	char	reg;

	reg = (char)lex.args[param].reg;
	write(fd, &reg, 1);
}
