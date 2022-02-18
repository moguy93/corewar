/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_labels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 14:32:39 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 14:33:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline bool			check_presence(t_label *labels, unsigned int n,
												char *try, unsigned int *stick)
{
	unsigned int		i;
	size_t				len;
	size_t				try_len;

	i = 0;
	try_len = 0;
	while (is_label_char(try[try_len]))
		try_len++;
	while (i < n && labels[i].ptr)
	{
		len = 0;
		while (is_label_char(labels[i].ptr[len]))
			len++;
		if (len == try_len && !ft_strncmp(labels[i].ptr, try, len))
		{
			*stick = labels[i].stick;
			return (true);
		}
		i++;
	}
	return (false);
}

static inline int			add_label(t_env *env, unsigned int i)
{
	static int		index = 0;
	unsigned int	len;

	len = 0;
	i--;
	while (is_label_char(env->file[i])
		&& env->file[i] != '\n' && i > 0)
		i--;
	i++;
	if (check_presence(env->labels, env->nb_labels, &env->file[i], &len)
		&& dup_label_err(env->file, i, len))
		return (-1);
	env->labels[env->lab_i].ptr = &env->file[i];
	env->labels[env->lab_i].stick = i;
	while (env->file[i] != ':')
	{
		len++;
		i++;
	}
	env->labels[env->lab_i].len = len;
	env->lab_i++;
	index++;
	return (0);
}

static inline unsigned int	count_labels(t_env *env)
{
	unsigned int	ret;
	unsigned int	i;

	i = 0;
	ret = 0;
	while (env->file[i])
	{
		cross_whitespace(env->file, &i);
		if (!is_label_char(env->file[i]))
		{
			cross_line(env->file, &i);
			continue ;
		}
		cross_names(env->file, &i);
		if (env->file[i] && env->file[i] == ':')
			ret++;
		cross_line(env->file, &i);
	}
	return (ret);
}

static inline int			load_labels(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (env->file[i])
	{
		cross_whitespace(env->file, &i);
		if (!is_label_char(env->file[i]))
		{
			cross_line(env->file, &i);
			continue ;
		}
		cross_names(env->file, &i);
		if (env->file[i] && env->file[i] == ':')
			if (add_label(env, i) == -1)
				return (-1);
		cross_line(env->file, &i);
	}
	return (0);
}

int							init_labels(t_env *env)
{
	if ((env->nb_labels = count_labels(env)) == 0)
		return (0);
	if (!(env->labels = (t_label*)malloc(sizeof(t_label) * env->nb_labels)))
		return (-1);
	ft_memset(env->labels, 0, sizeof(t_label) * env->nb_labels);
	if (load_labels(env) != 0)
		return (-1);
	return (0);
}
