/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:40:45 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 04:14:38 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_lex_name_prop(t_env *env, t_token *tok)
{
	static bool		done = false;

	if (!tok || tok->type != TOK_P_NAME)
		return (0);
	if ((!tok->next || tok->next->type != TOK_STRING)
		&& !property_error(env->file, tok))
		return (-1);
	if (!tok->next->next || tok->next->next->type != TOK_NEWLINE)
	{
		expected_newline_err(tok);
		return (-1);
	}
	if (done)
		return (-1);
	done = true;
	return (LEX_NAME_PROP);
}

char	get_lex_comment_prop(t_env *env, t_token *tok)
{
	static bool		done = false;

	if (!tok || tok->type != TOK_P_COM)
		return (0);
	if ((!tok->next || tok->next->type != TOK_STRING)
		&& !property_error(env->file, tok))
		return (-1);
	if (!tok->next->next || tok->next->next->type != TOK_NEWLINE)
	{
		expected_newline_err(tok);
		return (-1);
	}
	if (done)
		return (-1);
	done = true;
	return (LEX_COMMENT_PROP);
}

char	get_lex_label(t_env *env, t_token *tok)
{
	(void)env;
	if (!tok || tok->type != TOK_LABEL)
		return (0);
	if (tok->next->type != TOK_OPCODE && tok->next->type != TOK_NEWLINE
		&& tok->next->type != TOK_LABEL)
		return (-1);
	tok = tok->next;
	while (tok && tok->type == TOK_NEWLINE)
		tok = tok->next;
	if (tok && tok->type != TOK_OPCODE && tok->type != TOK_LABEL)
		return (-1);
	return (LEX_LABEL);
}

char	get_lex_opcode(t_env *env, t_token *t)
{
	unsigned int	i;
	int				op;
	int				nb_params;

	i = 0;
	(void)env;
	if (!t || t->type != TOK_OPCODE)
		return (0);
	while (ft_is_whitespace(*t->ptr))
		t->ptr++;
	if ((op = find_op(t->ptr)) == -1
		|| (t->next && t->next->type == TOK_NEWLINE && not_eno_args(t, op)))
		return (-1);
	t = t->next;
	nb_params = 0;
	while (i < 9 && g_op_args[op][i] != 0)
	{
		nb_params++;
		i += 3;
	}
	if (check_opcode_params(t, op, nb_params) != 0)
		return (-1);
	return (LEX_OP);
}
