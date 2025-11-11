/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:54:54 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 15:24:48 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "minishell.h"
# include <errno.h>
# include <sys/wait.h>

typedef	int (*t_executor_func)(t_node *node, t_shell_context *context);

typedef struct s_pipe_data
{
	t_dlist	*pid_list;
	int		input_fd;
	int		last_status;
}	t_pipe_data;

int		executor(t_shell_context *context);
int		execute_node(t_node *node, t_shell_context *context);
int		handle_exec_cmd(t_node *node, t_shell_context *context);
int		handle_exec_pipe(t_node *node, t_shell_context *context);
int		handle_exec_list(t_node *node, t_shell_context *context);
int		handle_exec_and(t_node *node, t_shell_context *context);
int		handle_exec_or(t_node *node, t_shell_context *context);
int		handle_exec_subshell(t_node *node, t_shell_context *context);
void	child_task(char *path, char **argv, char **envp);
char	**convert_env_to_array(t_hash_table *hash_items);
char	*find_command_path(t_hash_table *env, char *cmd);
int		parent_wait_task(pid_t pid);
int		print_error(char *s1, char *s2, int fd);
int		reset_close_fd(int *std_bak, int val);
bool	is_builtin(const char *cmd);
char	**copy_args(t_dlist *lst);

#endif
