/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:35:58 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/29 11:30:12 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_node	*build_and_or(t_node *left_node, t_token_kind kind, t_dlist *tokens)
{
	t_node			*right_node;
	t_bin_node		*new_ast;

	right_node = parse_pipeline(tokens);
	if (!right_node)
	{
		free_node(left_node);
		return (NULL);
	}
	if (kind == TK_AND)
		new_ast = new_bin_node(NK_AND, left_node, right_node);
	else
		new_ast = new_bin_node(NK_OR, left_node, right_node);
	if (!new_ast)
	{
		free_node(left_node);
		free_node(right_node);
		return (NULL);
	}
	left_node = (t_node *) new_ast;
	return (left_node);
}

t_node	*parse_and_or(t_dlist *tokens)
{
	t_node			*left_node;
	t_token_kind	kind;

	if (!tokens || !tokens->size)
		return (NULL);
	left_node = parse_pipeline(tokens);
	if (!left_node)
		return (NULL);
	while (tokens->size)
	{
		kind = ((t_token *)tokens->head->content)->kind;
		if (kind != TK_AND && kind != TK_OR)
			break ;
		ft_dlstremove_node(tokens, tokens->head, free_token);
		if (!tokens->size || is_invalid_operator((t_token *)tokens->head->content))
		{
			free_node(left_node);
			return (NULL);
		}
		left_node = build_and_or(left_node, kind, tokens);
		if (!left_node)
			return (NULL);
	}
	return (left_node);
}
