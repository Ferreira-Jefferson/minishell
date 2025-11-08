/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:44:31 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/08 16:18:32 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_cmd_node	*new_cmd_node(void)
{
	t_cmd_node	*node;

	node = ft_calloc(1, sizeof(t_cmd_node));
	if (!node)
		return (NULL);
	node->base.kind = NK_COMMAND;
	node->args = ft_dlstinit();
	node->redirections = ft_dlstinit();
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	if (!node->redirections)
	{
		ft_dlstdestroy(&node->args, free);
		free(node);
		return (NULL);
	}
	return (node);
}

t_bin_node	*new_bin_node(t_node_kind kind, t_node *left, t_node *right)
{
	t_bin_node	*node;

	node = ft_calloc(1, sizeof(t_bin_node));
	if (!node)
		return (NULL);
	node->base.kind = kind;
	node->left = left;
	node->right = right;
	return (node);
}

t_pipe_node	*new_pipe_node(void)
{
	t_pipe_node	*node;

	node = ft_calloc(1, sizeof(t_pipe_node));
	if (!node)
		return (NULL);
	node->base.kind = NK_PIPE;
	node->commands = ft_dlstinit();
	if (!node->commands)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_sub_node	*new_sub_node(t_node *sub_ast)
{
	t_sub_node	*node;

	if (!sub_ast)
		return (NULL);
	node = ft_calloc(1, sizeof(t_sub_node));
	if (!node)
		return (NULL);
	node->base.kind = NK_SUBSHELL;
	node->sub_ast = sub_ast;
	return (node);
}

t_redir	*new_redir(t_redir_kind kind, char *filename)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->kind = kind;
	redir->filename = filename;
	return (redir);
}
