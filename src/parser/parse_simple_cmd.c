/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:14:36 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 19:24:09 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static bool	build_redir(t_cmd_node *cmd_node, t_token *token, t_redir_kind kind)
{
	t_redir	*redir;

	redir = new_redir(kind, token->lexeme);
	if (!redir)
	{
		free_token(token);
		free_node(cmd_node);
		return (false);
	}
	if (!ft_dlstpush_back(cmd_node->redirections, redir))
	{
		free_redir(redir);
		free(token);
		free_node(cmd_node);
		return (false);
	}
	return (true);
}

static bool	handle_redirection(t_cmd_node *cmd_node, t_dlist *tokens)
{
	t_redir_kind	kind;
	t_token			*token;

	token = (t_token *)ft_dlstpop_front(tokens);
	kind = get_redir_kind(token);
	free_token(token);
	token = (t_token *)ft_dlstpeek_front(tokens);
	if (!token || token->kind != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!token || token->kind == TK_EOF)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(((char *)token->lexeme), 2);
		ft_putstr_fd("'\n", 2);
		free_node(cmd_node);
		return (false);
	}
	token = (t_token *)ft_dlstpop_front(tokens);
	if (!build_redir(cmd_node, token, kind))
		return (false);
	free(token);
	return (true);
}

static bool	build_simple_cmd(t_cmd_node *cmd_node, t_token *token, \
	t_dlist *tokens)
{
	if (token->kind == TK_WORD)
	{
		token = (t_token *)ft_dlstpop_front(tokens);
		if (!ft_dlstpush_back(cmd_node->args, token->lexeme))
		{
			free_token(token);
			free_node(cmd_node);
			return (false);
		}
		free(token);
	}
	else if (is_redirection(token->kind))
	{
		if (!handle_redirection(cmd_node, tokens))
			return (false);
	}
	return (true);
}

t_node	*parse_simple_cmd(t_dlist *tokens)
{
	t_cmd_node		*cmd_node;
	t_token			*token;

	if (!tokens || !tokens->size)
		return (NULL);
	cmd_node = new_cmd_node();
	if (!cmd_node)
		return (NULL);
	while (tokens->size && !is_operator((t_token *)tokens->head->content))
	{
		token = (t_token *)ft_dlstpeek_front(tokens);
		if (!build_simple_cmd(cmd_node, token, tokens))
			return (NULL);
	}
	return ((t_node *)cmd_node);
}
