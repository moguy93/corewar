/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:58:18 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/21 02:51:13 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	write_content(t_env *env, int fd,
							char buff[HEADER_SIZE], char lbe_buff[LBE_BUFFER])
{
	reverse_bits(lbe_buff, COREWAR_EXEC_MAGIC);
	write(fd, lbe_buff, LBE_BUFFER);
	ft_memset(buff, 0, sizeof(char) * HEADER_SIZE);
	ft_strcpy(buff, env->p_name);
	write(fd, buff, PROG_NAME_LENGTH);
	ft_memset(lbe_buff, PADDING_VALUE, sizeof(char) * LBE_BUFFER);
	write(fd, lbe_buff, LBE_BUFFER);
	reverse_bits(lbe_buff, env->bin_size);
	write(fd, lbe_buff, LBE_BUFFER);
	ft_memset(buff, 0, sizeof(char) * HEADER_SIZE);
	ft_strcpy(buff, env->p_comment);
	write(fd, buff, COMMENT_LENGTH);
	ft_memset(lbe_buff, PADDING_VALUE, sizeof(char) * LBE_BUFFER);
	write(fd, lbe_buff, LBE_BUFFER);
}

static inline int	get_op_size(t_lexem *lex)
{
	int		ret;

	ret = 0;
	if (lex->encoding & 128 && lex->encoding & 64)
		ret += IND_SIZE;
	if ((lex->encoding & 128) && !(lex->encoding & 64))
		ret += g_direct_size[(int)lex->opcode];
	if (!(lex->encoding & 128) && (lex->encoding & 64))
		ret++;
	if (lex->encoding & 32 && lex->encoding & 16)
		ret += IND_SIZE;
	if ((lex->encoding & 32) && !(lex->encoding & 16))
		ret += g_direct_size[(int)lex->opcode];
	if (!(lex->encoding & 32) && (lex->encoding & 16))
		ret++;
	if (lex->encoding & 8 && lex->encoding & 4)
		ret += IND_SIZE;
	if ((lex->encoding & 8) && !(lex->encoding & 4))
		ret += g_direct_size[(int)lex->opcode];
	if (!(lex->encoding & 8) && (lex->encoding & 4))
		ret++;
	return (ret);
}

static inline int	compute_bytecode_size(t_env *env)
{
	unsigned int	i;
	int				ret;

	i = 0;
	ret = 0;
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_LABEL)
			env->lexemes[i].start_byte = (unsigned int)ret;
		else if (env->lexemes[i].type == LEX_OP)
		{
			env->lexemes[i].start_byte = (unsigned int)ret;
			ret++;
			if (env->lexemes[i].code)
				ret++;
			ret += get_op_size(&env->lexemes[i]);
		}
		i++;
	}
	return (ret);
}

static inline char	*get_lex_string(t_env *env, char id)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == id)
			return (env->lexemes[i].args[0].str);
		i++;
	}
	return (NULL);
}

int					write_header(t_env *env, int *fd)
{
	char	buff[HEADER_SIZE];
	char	lbe_buff[LBE_BUFFER];

	if (!(env->p_name = get_lex_string(env, LEX_NAME_PROP))
		|| !(env->p_comment = get_lex_string(env, LEX_COMMENT_PROP)))
		return (1);
	if ((env->bin_size = compute_bytecode_size(env)) <= 0)
	{
		ft_putendl_fd(EMPTY_OP_SECTION, 2);
		return (-1);
	}
	if ((*fd = open(env->bin_name, O_CREAT | O_WRONLY, 444)) < 0)
		return (-1);
	write_content(env, *fd, buff, lbe_buff);
	return (0);
}
