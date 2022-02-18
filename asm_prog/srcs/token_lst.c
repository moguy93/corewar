/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:28:12 by gedemais          #+#    #+#             */
/*   Updated: 2020/01/15 20:28:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	token_free_lst(t_token *lst)
{
	if (lst->next)
		token_free_lst(lst->next);
	free(lst);
}

void	token_snap_node(t_token **lst, t_token *node)
{
	t_token		*tmp;

	tmp = (*lst);
	if (node == *lst)
	{
		node = node->next;
		free(*lst);
		*lst = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	if (node == tmp)
	{
		tmp->prev->next = NULL;
		free(tmp);
		return ;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
}

int		token_pushfront(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!(*lst))
	{
		(*lst) = new;
		(*lst)->prev = NULL;
		(*lst)->next = NULL;
	}
	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = NULL;
	return (0);
}

t_token	*token_lstnew(t_env *env, t_tokenizer *tok)
{
	t_token	*new;

	if (!(new = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	new->type = tok->ret;
	new->ptr = &env->file[tok->i - tok->len];
	new->next = NULL;
	while (*new->ptr && ft_is_whitespace(*new->ptr))
		new->ptr++;
	new->label = -1;
	new->len = tok->len;
	new->index = tok->i;
	new->line = tok->line;
	new->col = tok->col;
	return (new);
}
