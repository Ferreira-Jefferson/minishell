/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 09:41:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/29 10:39:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	build_pipeline(t_pipe_node *pipe_node, t_dlist *tokens)
{
	t_node	*cmd_node;

	while (tokens->size && ((t_token *)tokens->head->content)->kind == TK_PIPE)
	{
		ft_dlstremove_node(tokens, tokens->head, free_token);
		if (!(t_token *)tokens->head || is_invalid_operator((t_token *)tokens->head->content))
		{
			free_node(pipe_node);
			return (false);
		}
		cmd_node = parse_primary(tokens);
		if (!cmd_node)
		{
			free_node(pipe_node);
			return (false);
		}
		if (!ft_dlstpush_back(pipe_node->commands, cmd_node))
		{
			free_node(pipe_node);
			free_node(cmd_node);
			return (false);
		}
	}
	return (true);
}

static t_pipe_node	*init_pipe_node(t_node *cmd_node)
{
	t_pipe_node	*pipe_node;

	pipe_node = new_pipe_node();
	if (!pipe_node)
	{
		free_node(cmd_node);
		return (NULL);
	}
	if (!ft_dlstpush_back(pipe_node->commands, cmd_node))
	{
		free_node(cmd_node);
		free_node(pipe_node);
		return (NULL);
	}
	return (pipe_node);
}

t_node	*parse_pipeline(t_dlist *tokens)
{
	t_node	*cmd_node;
	t_pipe_node	*pipe_node;
	t_token	*token;

	if (!tokens || !tokens->size)
		return (NULL);
	cmd_node = parse_primary(tokens);
	if (!cmd_node)
		return (NULL);
	token = (t_token *)ft_dlstpeek_front(tokens);
	if (token->kind != TK_PIPE)
		return (cmd_node);
	pipe_node = init_pipe_node(cmd_node);
	if (!pipe_node)
		return (NULL);
	if (!build_pipeline(pipe_node, tokens))
		return (NULL);
	return ((t_node *)pipe_node);
}
