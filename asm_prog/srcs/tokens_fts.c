/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_fts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:29:54 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 20:40:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_tok_number(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 0;
	if (!ft_isdigit(stream[0]) && stream[0] != '-' && stream[0] != '+')
		return (0);
	while (stream[j]
		&& (ft_isdigit(stream[j]) || stream[j] == '-' || stream[j] == '+'))
		j++;
	if (j == 0)
		return (0);
	*i += j;
	return (TOK_NUMBER);
}

char	get_tok_lnumber(t_env *env, char *stream, unsigned int *i)
{
	unsigned int	j;

	(void)env;
	j = 1;
	if (stream[0] != '%')
		return (0);
	if (stream[j] == '-' || stream[j] == '+')
		j++;
	while (stream[j] && ft_isdigit(stream[j]))
		j++;
	if (j == 1)
		return (0);
	*i += j;
	return (TOK_LNUMBER);
}

char	get_tok_dlaba(t_env *env, char *stream, unsigned int *i)
{
	size_t	size;

	size = 2;
	if (stream[0] != '%' || stream[1] != ':')
		return (0);
	while (is_label_char(stream[size]))
		size++;
	if (!is_label(env, &stream[2]) && !undefined_label_err(env))
		return (-1);
	*i += size;
	return (TOK_DLABA);
}

char	get_tok_indlaba(t_env *env, char *stream, unsigned int *i)
{
	size_t	size;

	size = 1;
	if (stream[0] != ':')
		return (0);
	while (is_label_char(stream[size]))
		size++;
	if (size == 1)
		return (0);
	if (!is_label(env, &stream[1]) && !undefined_label_err(env))
		return (-1);
	*i += size;
	return (TOK_INDLABA);
}
