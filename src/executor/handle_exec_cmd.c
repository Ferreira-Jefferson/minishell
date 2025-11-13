/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:14:16 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/13 13:34:52 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
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

static void	handle_not_built_in(t_shell_context *context, char **argv, char **envp, char *path)
{
	if (b_set(context, argv) == 0)
		return ;
	child_task(path, argv, envp);
}
	
static int	execute_builtin(t_dlist *args, t_shell_context *context)
{
	if (!ft_strcmp((char *)args->head->content, "echo"))
		return (b_echo(context, args));
	if (!ft_strcmp((char *)args->head->content, "cd"))
		return (b_cd(context, args));
	if (!ft_strcmp((char *)args->head->content, "pwd"))
		return (b_pwd(context, args));
	if (!ft_strcmp((char *)args->head->content, "export"))
		return (b_export(context, args));
	if (!ft_strcmp((char *)args->head->content, "unset"))
		return (b_unset(context, args));
	if (!ft_strcmp((char *)args->head->content, "env"))
		return (b_env(context, args));
	if (!ft_strcmp((char *)args->head->content, "exit"))
		return (b_exit(context, args));
	return (1);
}

static int	execute_execve(char **argv, t_shell_context *context)
{
	char	*path;
	char	**envp;
	pid_t	pid;
	int		status;

	status = 1;
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
	{
		handle_not_built_in(context, argv, envp, path);
		free_arr(envp);
		free(path);
	}
	else
	{
		status = parent_wait_task(pid);
		free(path);
		free_arr(envp);
	}
	return (status);
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

int	handle_exec_cmd(t_node *node, t_shell_context *context)
{
	t_cmd_node	*cmd_node;
	int			std_bak[2];
	int			status;

	cmd_node = (t_cmd_node *)node;
	std_bak[0] = dup(STDIN_FILENO);
	std_bak[1] = dup(STDOUT_FILENO);
	if (std_bak[0] == -1 || std_bak[1] == -1)
		return (1);
	if (ft_dlstforeach(cmd_node->redirections, apply_redir))
		status = 1;
	else if (!cmd_node->args || !cmd_node->args->size)
		status = 0;
	else
		status = execute_cmd(cmd_node->args, context);
	reset_close_fd(std_bak, 0);
	return (status);
}

