/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:00:31 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/03 14:49:30 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	is_redirection(t_token_kind kind)
{
	return (kind == TK_REDIR_IN
		|| kind == TK_REDIR_OUT
		|| kind == TK_HEREDOC
		|| kind == TK_APPEND);
}

int	is_invalid_operator(t_token *token)
{
	t_token_kind	kind;

	kind = token->kind;
	return (kind == TK_PIPE \
			|| kind == TK_AND \
			|| kind == TK_OR \
			|| kind == TK_LIST \
			|| kind == TK_EOF);
}

int	is_operator(t_token *token)
{
	t_token_kind	kind;

	kind = token->kind;
	return (kind == TK_PIPE
		|| kind == TK_AND
		|| kind == TK_OR
		|| kind == TK_LIST
		|| kind == TK_LPAREN
		|| kind == TK_RPAREN
		|| kind == TK_EOF);
}

t_redir_kind	get_redir_kind(t_token *token)
{
	if (token->kind == TK_REDIR_IN)
		return (RK_INPUT);
	if (token->kind == TK_REDIR_OUT)
		return (RK_OUTPUT);
	if (token->kind == TK_HEREDOC)
		return (RK_HEREDOC);
	if (token->kind == TK_APPEND)
		return (RK_APPEND);
	return (-1);
}

void	free_node(void *data)
{
	t_node	*node;

	if (!data)
		return ;
	node = (t_node *)data;
	if (node->kind == NK_COMMAND)
		free_cmd_node((t_cmd_node *)node);
	else if (node->kind == NK_LIST \
			|| node->kind == NK_OR \
			|| node->kind == NK_AND)
		free_bin_node((t_bin_node *)node);
	else if (node->kind == NK_PIPE)
		free_pipe((t_pipe_node *)node);
	else
		free_sub_node((t_sub_node *)node);
}
