/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:13:56 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:14:29 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_err_name(char *err)
{
	ft_putstr_fd(L_RED, 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(STOP, 2);
}

void	print_cursor(char *line, unsigned int col)
{
	unsigned int	i;

	i = 0;
	ft_putstr_fd(L_RED, 2);
	while (i < col)
	{
		if (ft_is_whitespace(line[i]))
			ft_putchar_fd(line[i], 2);
		else
			ft_putchar_fd(' ', 2);
		i++;
	}
	ft_putchar_fd('^', 2);
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(STOP, 2);
}

void	print_line_n_col(unsigned int line, unsigned int col, bool colon)
{
	char		*nline;
	char		*ncol;

	if (!(nline = ft_itoa((int)line + 1))
		|| !(ncol = ft_itoa((int)col)))
		return ;
	ft_putstr_fd(LINE, 2);
	ft_putstr_fd(nline, 2);
	free(nline);
	ft_putstr_fd(COL, 2);
	ft_putstr_fd(ncol, 2);
	free(ncol);
	if (colon)
		ft_putendl_fd(":", 2);
}

int		get_type_str(int id, char *buff)
{
	if (id == TOK_REG)
	{
		ft_strcpy(buff, "reg");
		return (0);
	}
	else if (id == TOK_NUMBER)
	{
		ft_strcpy(buff, "indirect_num");
		return (0);
	}
	else if (id == TOK_LNUMBER)
	{
		ft_strcpy(buff, "direct_num");
		return (0);
	}
	return (1);
}

int		missing_properity(bool name, bool comment)
{
	if (name)
		ft_putstr_fd("name ", 2);
	if (name && comment)
	{
		ft_putstr_fd(STOP, 2);
		ft_putstr_fd("and", 2);
	}
	if (comment)
		ft_putstr_fd(" comment ", 2);
	ft_putstr_fd(L_RED, 2);
	ft_putendl_fd(MISSING_PROPERITY, 2);
	ft_putstr_fd(STOP, 2);
	return (1);
}
