/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fts_ter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:31:06 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 03:26:48 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_tok_p_name(t_env *env, char *stream, unsigned int *i)
{
	static bool	done = false;
	size_t		prop_len;

	(void)env;
	prop_len = ft_strlen(NAME_CMD_STRING);
	if (stream[0] != '.')
		return (0);
	if (!ft_strncmp(NAME_CMD_STRING, stream, prop_len))
	{
		if (done && dup_properity_err(env->file, *i))
			return (-1);
		done = true;
		*i += prop_len;
		return (TOK_P_NAME);
	}
	return (0);
}

char	get_tok_p_com(t_env *env, char *stream, unsigned int *i)
{
	static bool	done = false;
	size_t		prop_len;

	(void)env;
	prop_len = ft_strlen(COMMENT_CMD_STRING);
	if (stream[0] != '.')
		return (0);
	if (!ft_strncmp(COMMENT_CMD_STRING, stream, prop_len))
	{
		if (done && dup_properity_err(env->file, *i))
			return (-1);
		done = true;
		*i += prop_len;
		return (TOK_P_COM);
	}
	unknown_properity(stream);
	return (-1);
}

char	get_tok_string(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (stream[0] != '"')
		return (0);
	while (stream[j] && stream[j] != '"')
		j++;
	if (!stream[j] || stream[j] != '"')
		return (0);
	*i += j + 1;
	return (TOK_STRING);
}

char	get_tok_reg(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;
	long long int	id;

	(void)env;
	j = 1;
	if (stream[0] != 'r')
		return (0);
	while (stream[j] && ft_isdigit(stream[j]))
		j++;
	id = ft_atoi(&stream[1]);
	if (j == 1 || j > 3 || id > REG_NUMBER || id <= 0)
	{
		ft_putstr_fd("Wrong register index ", 2);
		ft_putnbr_fd((int)id, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	*i += j;
	return (TOK_REG);
}
