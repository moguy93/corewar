/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:13:39 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 20:34:08 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	cross_whitespaces(char *stream, unsigned int *i)
{
	char	c;

	while (stream[*i])
	{
		c = stream[*i];
		if (c == '\n' || !ft_is_whitespace(c))
			break ;
		*i += 1;
	}
}

void	cross_whitespace(char *stream, unsigned int *i)
{
	while (stream[*i] && ft_is_whitespace(stream[*i]))
		*i += 1;
}

void	cross_names(char *stream, unsigned int *i)
{
	while (is_label_char(stream[*i]))
		*i += 1;
}

void	cross_line(char *stream, unsigned int *i)
{
	while (stream[*i] && stream[*i] != '\n')
		*i += 1;
}
