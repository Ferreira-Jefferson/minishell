/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:29:33 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/13 16:09:30 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	expand_text(char **line_ptr, t_shell_context *context)
{
	t_dnode	*fake_node;

	fake_node = ft_dlstnew(*line_ptr);
	if (!fake_node)
		return (1);
	expander(context, fake_node);
	*line_ptr = (char *)fake_node->content;
	ft_dlstdelone(fake_node, NULL);
	return (0);
}

static int	write_file(int fd, char *delimiter, t_shell_context *context)
{
	char	*line;
	rl_event_hook = ft_event_hook;
	while (1)
	{
		line = readline("> ");
		if (get_g_signal_status())
		{
			reset_g_signal_status();
			return (1);
		}
		if (!line)
		{
			print_here_error(delimiter, 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			return (free_str(line, 0));
		if (expand_text(&line, context))
			return (free_str(line, 1));
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

static int	create_file(char *filename, char *delimiter, t_shell_context *context)
{
	int	fd;
	int	status;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	status = write_file(fd, delimiter, context);
	close(fd);
	return (status);
}

static int	heredoc_check_callback(void *data, void *context_data)
{
	t_redir			*redir;
	t_shell_context	*context;
	char			*tmp_filename;
	char			*delimiter;

	redir = (t_redir *)data;
	context = (t_shell_context *)context_data;
	if (redir->kind != RK_HEREDOC)
		return (0);
	tmp_filename = gen_filename();
	if (!tmp_filename)
		return (1);
	delimiter = redir->filename;
	if (create_file(tmp_filename, delimiter, context) || !ft_dlstpush_back(context->heredoc_files, tmp_filename))
	{
		unlink(tmp_filename);
		free(tmp_filename);
		return (1);
	}
	unlink(tmp_filename);
	free(redir->filename);
	redir->filename = ft_strdup(tmp_filename);
	if (!redir->filename)
		return (1);
	return (0);
}

int	handle_traveler_cmd(t_node *node, t_shell_context *context)
{
	t_cmd_node	*cmd_node;

	cmd_node = (t_cmd_node *)node;
	context->heredoc_files = ft_dlstinit();
	if (!context->heredoc_files)
		return (1);
	return (ft_dlstforeach_ctx(cmd_node->redirections,
		heredoc_check_callback, context));
}

