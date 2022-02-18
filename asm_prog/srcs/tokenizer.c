/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 18:14:17 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 20:29:33 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline int	crush_tokens(t_env *env)
{
	t_token	*t;

	t = env->tokens;
	while (t)
	{
		if (t->type == TOK_DLABA || t->type == TOK_INDLABA)
		{
			t->label = find_label_index(env->labels, t, env->nb_labels);
			t->type = (t->type == TOK_DLABA) ? TOK_LNUMBER : TOK_NUMBER;
		}
		if ((t->type == TOK_NEWLINE && t->next && t->next->type == TOK_NEWLINE)
			|| t->type == TOK_COMMENT
			|| (t == env->tokens && t->type == TOK_NEWLINE))
		{
			token_snap_node(&env->tokens, t);
			env->nb_tokens--;
			t = env->tokens;
			continue ;
		}
		t = t->next;
	}
	return (0);
}

static inline void	update_tok(char *stream, t_tokenizer *tok, unsigned int tmp)
{
	if (tok->ret == TOK_NEWLINE)
	{
		tok->line++;
		tok->line_start = tmp + 1;
	}
	tok->col = tok->i - tok->line_start;
	if (tok->ret == TOK_COMMENT)
		while (stream[tok->i] && stream[tok->i] != '\n')
			tok->i++;
	tok->len = tok->i - tmp;
}

static inline int	get_token_type(t_env *env, t_tokenizer *tok)
{
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	tmp = tok->i;
	while (i < NB_TOKENS_FUNCS)
	{
		if ((tok->ret = g_token_fts[i](env, &env->file[tok->i], &tok->i)))
		{
			if (tok->ret == -1)
				return (-1);
			update_tok(env->file, tok, tmp);
			break ;
		}
		update_tok(env->file, tok, tmp);
		i++;
	}
	return (0);
}

int					tokenizer(t_env *env)
{
	int		ret;

	ft_memset(&env->tok, 0, sizeof(t_tokenizer));
	if (init_labels(env) != 0)
		return (-1);
	while (env->file[env->tok.i])
	{
		cross_whitespaces(env->file, &env->tok.i);
		ret = get_token_type(env, &env->tok);
		if (ret == -1)
			return (-1);
		if (env->tok.ret == TOK_NONE && invalid_syntax_err(env, &env->tok) == 0)
			return (-1);
		if (token_pushfront(&env->tokens, token_lstnew(env, &env->tok)) != 0)
			return (-1);
		env->tok.index++;
	}
	env->nb_tokens = env->tok.index;
	if (crush_tokens(env) != 0)
		return (-1);
	return (0);
}
