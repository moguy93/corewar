/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:22:03 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 19:11:06 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline char	get_lexeme_type(t_env *env, t_token *tok)
{
	static char		(*g_lex_fts[NB_LEX_FUNCS])(t_env*, t_token*) = {
					&get_lex_name_prop,
					&get_lex_comment_prop,
					&get_lex_label,
					&get_lex_opcode};
	unsigned int	i;
	char			ret;

	i = 0;
	while (i < NB_LEX_FUNCS)
	{
		ret = g_lex_fts[i](env, tok);
		if (ret == -1)
		{
			unex_token(tok);
			return (-1);
		}
		if (ret > TOK_NONE)
			return (ret);
		i++;
	}
	return (0);
}

static inline int	load_lexeme(t_env *env, unsigned int lex,
													char type, t_token **tok)
{
	static int		(*load_lex_fts[NB_LEX_LOAD_FUNCS])(t_env*, t_lexem*,
					t_token**) = {&load_lex_name_prop,
					&load_lex_comment_prop,
					&load_lex_label,
					&load_lex_opcode};
	unsigned int	i;
	int				depth;

	i = 1;
	depth = 0;
	while (i < LEX_MAX)
	{
		if ((char)i == type &&
			(depth = load_lex_fts[i - 1](env, &env->lexemes[lex], tok)) == -1)
			return (-1);
		if (depth > 0)
			break ;
		i++;
	}
	while ((*tok) && depth > 0)
	{
		(*tok) = (*tok)->next;
		depth--;
	}
	return (0);
}

static inline int	check_properitys(t_token *tok)
{
	bool	name;
	bool	comment;

	name = true;
	comment = true;
	while (tok)
	{
		if (tok->type == TOK_P_NAME)
			name = false;
		if (tok->type == TOK_P_COM)
			comment = false;
		tok = tok->next;
	}
	if (name || comment)
	{
		missing_properity(name, comment);
		return (-1);
	}
	return (0);
}

int					lexer(t_env *env)
{
	t_token			*tmp;
	char			ret;

	tmp = env->tokens;
	if (!(env->lexemes = (t_lexem*)malloc(sizeof(t_lexem) * env->nb_tokens)))
		return (-1);
	ft_memset(env->lexemes, 0, sizeof(t_lexem) * env->nb_tokens);
	if (check_properitys(env->tokens) == -1)
		return (-1);
	while (tmp && tmp->next)
	{
		if ((ret = get_lexeme_type(env, tmp)) <= LEX_NONE
			|| load_lexeme(env, env->nb_lex, ret, &tmp) != 0)
		{
			free_lexemes(env);
			return (-1);
		}
		env->nb_lex++;
	}
	return (0);
}
