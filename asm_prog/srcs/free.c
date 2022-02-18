/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:38:04 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/08 19:11:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static inline void	free_strings(t_env *env)
{
	if (env->bin_name)
		free(env->bin_name);
	if (env->p_name)
		free(env->p_name);
	if (env->p_comment)
		free(env->p_comment);
}

void				free_lexemes(t_env *env)
{
	unsigned int	i;

	i = 0;
	while (i < env->nb_lex)
	{
		if (env->lexemes[i].type == LEX_NAME_PROP
			|| env->lexemes[i].type == LEX_COMMENT_PROP)
			free(env->lexemes[i].args[0].str);
		i++;
	}
}

int					free_env(t_env *env)
{
	if (env->file)
	{
		free(env->file);
		env->file = NULL;
	}
	if (env->tokens)
	{
		token_free_lst(env->tokens);
		env->tokens = NULL;
	}
	if (env->lexemes)
		free(env->lexemes);
	if (env->labels)
		free(env->labels);
	free_strings(env);
	return (0);
}
