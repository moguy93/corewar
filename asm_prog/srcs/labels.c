/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:27:34 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:39:37 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

bool						is_label_char(char c)
{
	unsigned int	i;

	i = 0;
	if (c == 0)
		return (false);
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (true);
		i++;
	}
	return (false);
}

bool						is_label(t_env *env, char *label)
{
	unsigned int	i;
	size_t			len;

	i = 0;
	len = 0;
	while (is_label_char(label[len]))
		len++;
	while (i < env->nb_labels && env->labels[i].ptr)
	{
		if (len == env->labels[i].len)
		{
			if (!ft_strncmp(label, env->labels[i].ptr, len))
				return (true);
		}
		i++;
	}
	return (false);
}

int							find_label_index(t_label *labs, t_token *tok,
														unsigned int nb_labels)
{
	unsigned int	offset;
	unsigned int	len;
	unsigned int	less;
	int				ret;
	int				i;

	i = 0;
	ret = -1;
	less = 0;
	offset = (tok->type == TOK_DLABA || tok->type == TOK_LNUMBER) ? 2 : 1;
	while (i < (int)nb_labels)
	{
		len = 0;
		while (is_label_char(labs[i].ptr[len]))
			len++;
		if (len >= less && len == labs[i].len
			&& !ft_strncmp(&tok->ptr[offset], labs[i].ptr, len))
		{
			less = len;
			ret = i;
		}
		i++;
	}
	return (ret);
}
