/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:26:58 by gedemais          #+#    #+#             */
/*   Updated: 2020/02/20 03:10:53 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		undefined_label_err(t_env *env)
{
	unsigned int	i;

	i = 0;
	print_err_name(UNDEFINED_LABEL);
	print_line_n_col(env->tok.line, env->tok.col, true);
	while (env->file[env->tok.line_start + i]
		&& env->file[env->tok.line_start + i] != '\n')
	{
		ft_putchar_fd(env->file[env->tok.line_start + i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	print_cursor(&env->file[env->tok.line_start], env->tok.col);
	ft_putstr_fd(STOP, 2);
	return (0);
}

int		invalid_label_err(t_token *tok)
{
	unsigned int	i;

	i = 0;
	print_err_name(INVALID_LABEL);
	print_line_n_col(tok->line, tok->col, true);
	while (tok->ptr[i] && tok->ptr[i] != '\n')
	{
		ft_putchar_fd(tok->ptr[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

int		dup_label_err(char *label, unsigned int i, unsigned int first)
{
	unsigned int	j;

	j = 0;
	print_err_name(DUP_LABEL);
	ft_putchar_fd('\n', 2);
	while (label[first] && label[first] != '\n')
	{
		ft_putchar_fd(label[first], 2);
		first++;
	}
	ft_putchar_fd('\n', 2);
	while (label[i] && label[i] != '\n')
	{
		ft_putchar_fd(label[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (1);
}

int		expected_newline_err(t_token *tok)
{
	char		*nline;

	if (!(nline = ft_itoa(tok->line)))
		return (-1);
	print_err_name(EX_NEWLINE);
	ft_putstr_fd(LINE, 2);
	ft_putendl_fd(nline, 2);
	free(nline);
	return (0);
}

int		unknown_properity(char *stream)
{
	unsigned int	i;

	i = 0;
	print_err_name(UNKNOWN_PROPERITY);
	ft_putstr_fd(": ", 2);
	while (stream[i] && stream[i] != '\n')
		i++;
	write(2, stream, i);
	ft_putchar_fd('\n', 2);
	return (0);
}
