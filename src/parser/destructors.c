/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:59:53 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 15:50:29 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	free_redir(void *data)
{
	t_redir	*redir;

	if (!data)
		return ;
	redir = (t_redir *)data;
	free(redir->filename);
	free(redir);
}

void	free_cmd_node(t_cmd_node *node)
{
	if (!node)
		return ;
	ft_dlstdestroy(&node->args, free);
	ft_dlstdestroy(&node->redirections, free_redir);
	free(node);
}

void	free_bin_node(t_bin_node *node)
{
	if (!node)
		return ;
	free_node(node->left);
	free_node(node->right);
	free(node);
}

void	free_sub_node(t_sub_node *node)
{
	if (!node)
		return ;
	free_node(node->sub_ast);
	free(node);
}

void	free_pipe(t_pipe_node *node)
{
	if (!node)
		return ;
	ft_dlstdestroy(&node->commands, free_node);
	free(node);
}
