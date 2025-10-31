/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:35:07 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/31 10:45:15 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_node	*build_list(t_dlist *tokens, t_node *left_node)
{
	t_node		*right_node;
	t_bin_node	*new_ast;

	right_node = parse_and_or(tokens);
	if (!right_node)
	{
		free_node(left_node);
		return (NULL);
	}
	new_ast = new_bin_node(NK_LIST, left_node, right_node);
	if (!new_ast)
	{
		free_node(left_node);
		free_node(right_node);
		return (NULL);
	}
	return ((t_node *) new_ast);
}

t_node	*parse_cmd_list(t_dlist *tokens)
{
	t_node			*left_node;

	if (!tokens || !tokens->size)
		return (NULL);
	left_node = parse_and_or(tokens);
	if (!left_node)
		return (NULL);
	while (tokens->size && ((t_token *)tokens->head->content)->kind == TK_LIST)
	{
		ft_dlstremove_node(tokens, tokens->head, free_token);
		if (tokens->size && ((t_token *)tokens->head->content)->kind == TK_EOF)
			break ;
		if (!tokens->size || is_invalid_operator(tokens->head->content))
		{
			free_node(left_node);
			return (NULL);
		}
		left_node = build_list(tokens, left_node);
		if (!left_node)
			return (NULL);
	}
	return (left_node);
}
