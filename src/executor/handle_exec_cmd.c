/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:14:16 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 16:11:15 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	apply_redir(void *data)
{
	t_redir	*redir;
	int		file_fd;
	int		std_input;

	redir = (t_redir *)data;
	file_fd = -1;
	std_input = -1;
	if (redir->kind == RK_INPUT || redir->kind == RK_HEREDOC)
	{
		file_fd = open(redir->filename, O_RDONLY);
		std_input = STDIN_FILENO;
	}
	if (redir->kind == RK_OUTPUT || redir->kind == RK_APPEND)
	{
		if (redir->kind == RK_OUTPUT)
			file_fd = open(redir->filename, O_WRONLY | O_CREAT |O_TRUNC);
		else
			file_fd = open(redir->filename, O_WRONLY | O_CREAT |O_APPEND);
		std_input = STDOUT_FILENO;
	}
	if (file_fd == -1)
		return (1);
	dup2(file_fd, std_input);
	close(file_fd);
	return (0);
}

static int	execute_cmd(t_dlist *lst, t_shell_context *context)
{
	char	**argv;
	int		status;

	if (is_builtin((const char *)lst->head->content))
		return (execute_builtin(lst, context));
	argv = copy_args(lst);
	if (!argv)
		return (1);
	status = execute_execve(argv, context);
	free(argv);
	return (status);
}

static int	execute_builtin(t_dlist *args, t_shell_context *context)
{
	if (!ft_strncmp((char *)args->head->content, "echo", 5))
		return (b_echo(context, args));
	else if (!ft_strncmp((char *)args->head->content, "cd", 3))
		return (b_cd(context, args));
	else if (!ft_strncmp((char *)args->head->content, "pwd", 4))
		return (b_pwd(context, args));
	else if (!ft_strncmp((char *)args->head->content, "export", 7))
		return (b_export(context, args));
	else if (!ft_strncmp((char *)args->head->content, "unset", 6))
		return (b_unset(context, args));
	else if (!ft_strncmp((char *)args->head->content, "env", 4))
		return (b_env(context));
	else if (!ft_strncmp((char *)args->head->content, "exit", 5))
		return (b_exit(context, args));
	else
		return (1);
}

static int	execute_execve(char **argv, t_shell_context *context)
{
	char	*path;
	char	**envp;
	pid_t	pid;
	int		status;

	path = find_command_path(context->env, argv[0]);
	envp = convert_env_to_array(context->env);
	if (!envp)
		return (free_str(path, 1));
	pid = fork();
	if (pid == -1)
	{
		free_arr(envp);
		return (free_str(path, 1));
	}
	if (pid == 0)
		child_task(path, argv, envp);
	else
	{
		status = parent_wait_task(pid);
		free(path);
		free_arr(envp);
	}
	return (status);
}

int	handle_exec_cmd(t_node *node, t_shell_context *context)
{
	t_cmd_node	*cmd_node;
	char		**argv;
	int			std_bak[2];
	int			status;

	cmd_node = (t_cmd_node *)node;
	std_bak[0] = dup(STDIN_FILENO);
	if (std_bak[0] == -1)
		return (1);
	std_bak[1] = dup(STDOUT_FILENO);
	if (std_bak[1] == -1)
	{
		close(std_bak[0]);
		return (1);
	}
	if (ft_dlstforeach(cmd_node->redirections, apply_redir))
		return (reset_close_fd(std_bak, 1));
	if (!cmd_node->args || !cmd_node->args->size)
		return (reset_close_fd(std_bak, 0));
	status = execute_cmd(cmd_node->args, context);
	return (reset_close_fd(std_bak, status));
}
