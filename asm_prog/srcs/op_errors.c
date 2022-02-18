/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:26:48 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 20:26:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					invalid_op_parameter(t_token *tok, int op)
{
	char				type[MAX_TYPE_SIZE];
	unsigned int		j;

	j = 0;
	print_err_name(INVALID_OP_PARAM);
	print_line_n_col(tok->line, tok->col, true);
	ft_putstr_fd("Incompatible type ", 1);
	get_type_str(tok->type, &type[0]);
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(STOP, 2);
	ft_putstr_fd(" for ", 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putendl_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (1);
}

int					too_few_op_args(t_token *tok, int op)
{
	print_err_name(TOO_FEW_ARGS);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col, true);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (0);
}

bool				check_after(t_token *tok)
{
	while (tok)
	{
		if (tok->type != TOK_NEWLINE)
			return (false);
		tok = tok->next;
	}
	return (true);
}

int					unex_token(t_token *tok)
{
	ft_putstr_fd(L_RED, 2);
	print_err_name(UNEX_TOKEN);
	ft_putstr_fd(STOP, 2);
	print_line_n_col(tok->line, tok->col, false);
	ft_putchar_fd('\n', 2);
	return (0);
}
