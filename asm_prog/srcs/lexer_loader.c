/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:15:53 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 04:41:32 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			load_lex_name_prop(t_env *env, t_lexem *lex, t_token **tok)
{
	char	*err;
	int		ret;

	ret = 2;
	if (!(*tok) || (*tok)->type != TOK_P_NAME)
		return (0);
	*tok = (*tok)->next;
	if (!(lex->args[0].str = ft_strndup(&(*tok)->ptr[1], (int)(*tok)->len - 2)))
		return (-1);
	if (ft_strlen(lex->args[0].str) >= PROG_NAME_LENGTH)
	{
		if (!(err = ft_itoa(PROG_NAME_LENGTH)))
			return (-1);
		ft_putstr_fd(NAME_LENGTH_ERR, 2);
		ft_putstr_fd(err, 2);
		ft_putendl_fd(" bytes.", 2);
		free(err);
		return (-1);
	}
	lex->type = LEX_NAME_PROP;
	lex->start = (unsigned int)((*tok)->ptr - env->file);
	return (ret);
}

int			load_lex_comment_prop(t_env *env, t_lexem *lex, t_token **tok)
{
	char	*err;
	int		ret;

	ret = 2;
	if (!(*tok) || (*tok)->type != TOK_P_COM)
		return (0);
	*tok = (*tok)->next;
	if (!(lex->args[0].str = ft_strndup(&(*tok)->ptr[1], (int)(*tok)->len - 2)))
		return (-1);
	if (ft_strlen(lex->args[0].str) >= COMMENT_LENGTH)
	{
		if (!(err = ft_itoa(COMMENT_LENGTH)))
			return (-1);
		ft_putstr_fd(COMMENT_LENGTH_ERR, 2);
		ft_putstr_fd(err, 2);
		ft_putendl_fd(" bytes.", 2);
		free(err);
		return (-1);
	}
	lex->type = LEX_COMMENT_PROP;
	lex->start = (unsigned int)((*tok)->ptr - env->file);
	return (ret);
}

int			load_lex_label(t_env *env, t_lexem *lex, t_token **tok)
{
	if (!(*tok) || (*tok)->type != TOK_LABEL)
		return (0);
	lex->type = LEX_LABEL;
	lex->start = (unsigned int)((*tok)->ptr - env->file);
	lex->args[0].nb = lex->start;
	lex->encoding = encoding_byte(lex->encoding, 0, TOK_NUMBER);
	return ((*tok)->next->type == TOK_NEWLINE ? 2 : 1);
}

static void	load_opcode_arg(t_env *env, t_lexem *lex, t_token *tmp,
																t_token **tok)
{
	long long int	ret;

	if (tmp->type == TOK_REG)
		lex->args[env->c_param].reg = (int)ft_atoi(&tmp->ptr[1]);
	else if (tmp->label >= 0
		&& (tmp->type == TOK_NUMBER || tmp->type == TOK_LNUMBER))
	{
		(*tok)->type = tmp->type;
		(*tok)->ptr = tmp->ptr;
		ret = find_label_index(env->labels, *tok, env->nb_labels);
		lex->label[env->c_param] = (int)ret;
	}
	else if (tmp->type == TOK_NUMBER || tmp->type == TOK_LNUMBER)
	{
		ret = ft_atoi(tmp->type == TOK_NUMBER ? tmp->ptr : &tmp->ptr[1]);
		lex->args[env->c_param].nb = ret;
	}
}

int			load_lex_opcode(t_env *env, t_lexem *lex, t_token **tok)
{
	t_token			*tmp;
	int				ret;

	tmp = (*tok);
	ret = 0;
	env->c_param = 0;
	if (!tmp || tmp->type != TOK_OPCODE)
		return (0);
	lex->type = LEX_OP;
	lex->start = (unsigned int)(tmp->ptr - env->file);
	lex->opcode = find_op(tmp->ptr);
	tmp = tmp->next;
	ft_memset(&lex->label, -1, sizeof(int) * MAX_ARGS_NUMBER);
	while (tmp && tmp->type != TOK_NEWLINE)
	{
		load_opcode_arg(env, lex, tmp, tok);
		lex->encoding = encoding_byte(lex->encoding, env->c_param, tmp->type);
		lex->code = encoding_byte_pres(lex->opcode);
		tmp = (tmp->next->type == TOK_SEPARATOR) ? tmp->next->next : tmp->next;
		env->c_param++;
		ret += 2;
	}
	return (ret + 1);
}
