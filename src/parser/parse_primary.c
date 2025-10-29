/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:41:17 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/29 09:41:33 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_node	*parse_primary(t_dlist *tokens)
{
	t_node	*sub_ast;
	t_token	*token;

	if (!tokens || !tokens->size)
		return (NULL);
	token = (t_token *)ft_dlstpeek_front(tokens);
	if (token->kind == TK_LPAREN)
	{
		ft_dlstremove_node(tokens, tokens->head, free_token);
		sub_ast = parse_cmd_list(tokens);
		if (!sub_ast)
			return (NULL);
		token = (t_token *)ft_dlstpeek_front(tokens);
		if (!token || token->kind != TK_RPAREN)
		{
			free_node(sub_ast);
			return (NULL);
		}
		ft_dlstremove_node(tokens, tokens->head, free_token);
		return ((t_node *)new_sub_node(sub_ast));
	}
	else if (token->kind == TK_WORD || is_redirection(token->kind))
		return (parse_simple_cmd(tokens));
	return (NULL);
}
