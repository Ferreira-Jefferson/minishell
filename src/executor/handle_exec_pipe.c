/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:32:08 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 10:27:08 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void parent_process_update(t_pipe_data *data, t_dnode *curr, int *pipefd)
{
	if (data->input_fd != STDIN_FILENO)
		close(data->input_fd);
	if (curr->next)
	{
		close(pipefd[1]);
		data->input_fd = pipefd[0];
	}
}

static void	child_process_exec(t_pipe_data *data, t_dnode *curr, int *pipefd, t_shell_context *context)
{
	int	status;

	dup2(data->input_fd, 0);
	if (curr ->next)
		dup2(pipefd[1], 1);
	if (data->input_fd != STDIN_FILENO)
		close(data->input_fd);
	if (curr->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	status = execute_node(curr->content, context);
	exit(status);
}

static int fork_pipeline(t_pipe_data *data, t_pipe_node *pipe_node, t_shell_context *context)
{
	t_dnode	*curr;
	int		pipefd[2];
	pid_t	pid;

	curr = pipe_node->commands->head;
	while (curr)
	{
		if (curr->next && pipe(pipefd) == -1)
			return (free_ret(&data->pid_list, NULL, NULL, 1));
		pid = fork();
		if (pid == -1)
			return (free_ret(&data->pid_list, NULL, NULL, 1));
		if (!ft_dlstpush_back(data->pid_list, (void *)(long)pid))
		{
			kill(pid, SIGKILL);
			waitpid(pid, NULL, 0);
			return (free_ret(&data->pid_list, NULL, NULL, 1));
		}
		if (pid == 0)
			child_process_exec(data, curr, pipefd, context);
		else
			parent_process_update(data, curr, pipefd);
		curr = curr->next;
	}
	return (0);
}

static int	wait_pipeline(t_pipe_data *data)
{
	t_dnode	*curr;
	pid_t	pid;
	int		temp_status;
	int		status;

	status = 1;
	curr = data->pid_list->head;
	while (curr)
	{
		pid = (pid_t)(long)curr->content;
		waitpid(pid, &temp_status, 0);
		if (curr == data->pid_list->tail)
		{
			if (WIFEXITED(temp_status))
				status = WEXITSTATUS(temp_status);
			else if (WIFSIGNALED(temp_status))
				status = 128 + WTERMSIG(temp_status);
			else
				status = 1;
		}
		curr = curr->next;
	}
	return (status);
}

int	handle_exec_pipe(t_node *node, t_shell_context *context)
{
	t_pipe_node		*pipe_node;
	t_pipe_data		*data;
	int				status;

	pipe_node = (t_pipe_node *)node;
	data = ft_calloc(1, sizeof(t_pipe_data));
	if (!data)
		return (1);
	data->pid_list = ft_dlstinit();
	if (!data->pid_list)
		return (free_ret(NULL, data, NULL, 1));
	data->input_fd = STDIN_FILENO;
	status = fork_pipeline(data, pipe_node, context);
	if (status)
		return (free_ret(&data->pid_list, data, NULL, 1));
	if (data->input_fd != STDIN_FILENO)
		close(data->input_fd);
	status = wait_pipeline(data);
	ft_dlstdestroy(&data->pid_list, NULL);
	free(data);
	return (status);
}
