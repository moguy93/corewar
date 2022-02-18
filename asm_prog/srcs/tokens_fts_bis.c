/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fts_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:33:03 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 03:55:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_tok_opcode(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;
	size_t			size;

	(void)env;
	j = 0;
	while (j < NB_OPS)
	{
		size = ft_strlen(g_opnames[j]);
		if (ft_strncmp(g_opnames[j], stream, size) == 0
			&& ft_is_whitespace(stream[size]))
		{
			*i += size;
			return (TOK_OPCODE);
		}
		j++;
	}
	return (0);
}

char	get_tok_separator(t_env *env, char *stream, unsigned int *i)
{
	(void)env;
	if (stream[0] == SEPARATOR_CHAR)
	{
		*i += 1;
		return (TOK_SEPARATOR);
	}
	return (0);
}

char	get_tok_label(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 0;
	if (!ft_isalnum(stream[0]))
		return (0);
	while (is_label_char(stream[j]))
		j++;
	if (stream[j] != LABEL_CHAR)
		return (0);
	*i += j + 1;
	return (TOK_LABEL);
}

char	get_tok_newline(t_env *env, char *stream, unsigned int *i)
{
	(void)env;
	if (stream[0] == '\n')
	{
		*i += 1;
		return (TOK_NEWLINE);
	}
	return (0);
}

char	get_tok_comment(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (stream[0] != COMMENT_CHAR && stream[0] != ';')
		return (0);
	while (stream[j] && stream[j] != '\n')
		j++;
	*i += j;
	return (TOK_COMMENT);
}
