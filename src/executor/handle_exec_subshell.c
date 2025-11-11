/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_subshell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 11:15:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/03 13:48:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_exec_subshell(t_node *node, t_shell_context *context)
{
	t_sub_node	*sub_node;
	int			status;
	pid_t		pid;

	sub_node = (t_sub_node *)node;
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		status = execute_node(sub_node->sub_ast, context);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (1);
}
