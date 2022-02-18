/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:13:23 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:13:26 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		property_error(char *file, t_token *tok)
{
	unsigned int	i;
	unsigned int	tmp;

	i = tok->index;
	print_err_name((tok->type == TOK_P_COM) ? COMMENT_CMD_ERR : NAME_CMD_ERR);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col, true);
	while (i > 0 && file[i] != '\n')
		i--;
	i++;
	tmp = i;
	while (file[i] != '\n')
	{
		ft_putchar_fd(file[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&file[tmp], tok->col);
	return (0);
}

int		invalid_syntax_err(t_env *env, t_tokenizer *tok)
{
	unsigned int	j;

	j = 0;
	print_err_name(INVALID_SYNTAX);
	print_line_n_col(tok->line, tok->col, true);
	while (env->file[tok->line_start + j]
		&& env->file[tok->line_start + j] != '\n')
	{
		ft_putchar_fd(env->file[tok->line_start + j], 2);
		j++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&env->file[tok->line_start], tok->col);
	return (0);
}

void	op_usage(int op)
{
	char			type[MAX_TYPE_SIZE];
	int				i;
	int				j;

	i = 0;
	ft_putstr_fd(BLUE, 2);
	ft_putstr_fd("Usage : ", 2);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putchar_fd(' ', 2);
	while (i < 9)
	{
		j = -1;
		ft_putstr_fd(g_op_args[op][i] ? "[" : 0, 2);
		while (++j < 3 && g_op_args[op][i + j])
		{
			if (get_type_str(g_op_args[op][i + j], &type[0]) != 0)
				return ;
			ft_putstr_fd(&type[0], 2);
			if (i + j + 1 < 9 && g_op_args[op][i + j + 1])
				ft_putstr_fd("|", 2);
		}
		ft_putstr_fd(g_op_args[op][i] ? "] " : 0, 2);
		i += 3;
	}
}

int		not_eno_args(t_token *tok, int op)
{
	unsigned int	i;

	i = 0;
	print_err_name(NOT_ENO_ARGS);
	ft_putstr_fd(L_GREEN, 2);
	ft_putstr_fd(g_opnames[op], 2);
	ft_putstr_fd(STOP, 2);
	ft_putchar_fd(' ', 2);
	print_line_n_col(tok->line, tok->col, true);
	op_usage(op);
	ft_putchar_fd('\n', 2);
	return (1);
}

int		dup_properity_err(char *file, unsigned int i)
{
	print_err_name(DUP_PROPERITY);
	while (file[i] && file[i] != '\n')
	{
		ft_putchar_fd(file[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}
