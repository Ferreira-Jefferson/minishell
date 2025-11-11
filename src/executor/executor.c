/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:49:29 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/02 10:52:35 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_node(t_node *node, t_shell_context *context)
{
	int								status;
	t_executor_func					handler;
	static const t_executor_func	executor_table[] = {
		&handle_exec_cmd,
		&handle_exec_pipe,
		&handle_exec_list,
		&handle_exec_and,
		&handle_exec_or,
		&handle_exec_subshell
	};

	if (!node)
		return (context->last_status);
	handler = executor_table[node->kind];
	status = handler(node, context);
	context->last_status = status;
	return (status);
}

int	executor(t_shell_context *context)
{
	execute_node(context->ast_root, context);
	free_node(context->ast_root);
	context->ast_root = NULL;
	return (context->last_status);
}
