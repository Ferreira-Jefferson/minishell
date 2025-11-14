/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:29:33 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/14 17:40:27 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	expand_text(char **line_ptr, t_shell_context *context)
{
	char	*newline;
	char	*str_aux;

	str_aux = str_new("");
	newline = *line_ptr;
	fprintf(stderr, "EXPAND_TEXT: (antes da expansão) Linha lida: [%s]\n", newline);
	ex_vars(context, newline, &str_aux, 2);
	*line_ptr = ft_strdup(str_aux);
	free(newline);
	str_free(str_aux);
	fprintf(stderr, "EXPAND_TEXT: (depois da expansão) Linha lida: [%s]\n", *line_ptr);
	return (0);
}

// static int	expand_text(char **line_ptr, t_shell_context *context)
// {
// 	t_dnode	*fake_node;
// 	char	*newline;

// 	newline = *line_ptr;
// 	fprintf(stderr, "EXPAND_TEXT: (antes da expansão) Linha lida: [%s]\n", newline);
// 	fake_node = ft_dlstnew(NULL);
// 	fake_node->content = str_new(newline);
// 	if (!fake_node || !fake_node->content)
// 	{
// 		if (fake_node)
// 			ft_dlstdelone(fake_node, NULL);
// 		return (1);
// 	}
// 	expander(context, fake_node);
// 	*line_ptr = (char *)fake_node->content;
// 	fprintf(stderr, "EXPAND_TEXT: (depois da expansão) Linha lida: [%s]\n", *line_ptr);
// 	free(newline);
// 	fake_node->content = NULL;
// 	ft_dlstdelone(fake_node, NULL);
// 	return (0);
// }

static int	write_file(int fd, char *delimiter, t_shell_context *context, int is_expandable)
{
	char	*line;
	fprintf(stderr, "HEREDOC: Iniciando. Delimitador é: [%s]\n", delimiter);
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
		fprintf(stderr, "HEREDOC: Linha lida: [%s]\n", line);
		if (ft_strcmp(line, delimiter) == 0)
		{
			fprintf(stderr, "HEREDOC: Delimitador encontrado. Saindo.\n");
			return (free_str(line, 0));
		}
		if (is_expandable && expand_text(&line, context))
		{
			fprintf(stderr, "HEREDOC: Erro de expansão. Saindo.\n");
			return (free_str(line, 1));
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

static int	create_file(char *filename, char *delimiter, t_shell_context *context)
{
	char	*new_delimiter;
	char	*remove_quotes;
	int	is_expandable;
	int	fd;
	int	status;

	is_expandable = 1;
	if (ft_strchr(delimiter, '"') || ft_strchr(delimiter, '\''))
		is_expandable = 0;
	new_delimiter = ft_strdup(delimiter);
	if (!new_delimiter)
		return (1);
	remove_quotes = remove_chars(new_delimiter, "\'\"");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(new_delimiter);
		return (1);
	}
	status = write_file(fd, remove_quotes, context, is_expandable);
	fprintf(stderr, "CREATE_FILE: retorno da função write_file: %d\n", status);
	close(fd);
	free(new_delimiter);
	return (status);
}

static int	heredoc_check_callback(void *data, void *context_data)
{
	t_redir			*redir;
	t_shell_context	*context;
	char			*tmp_filename;
	char			*filename_copy;

	redir = (t_redir *)data;
	context = (t_shell_context *)context_data;
	if (redir->kind != RK_HEREDOC)
		return (0);
	tmp_filename = gen_filename();
	if (!tmp_filename)
		return (1);
	if (create_file(tmp_filename, redir->filename, context) || !ft_dlstpush_back(context->heredoc_files, tmp_filename))
	{
		unlink(tmp_filename);
		free(tmp_filename);
		return (1);
	}
	filename_copy = ft_strdup(tmp_filename);
	if (!filename_copy)
		return (1);
	free(redir->filename);
	redir->filename = filename_copy;
	return (0);
}

int	handle_traveler_cmd(t_node *node, t_shell_context *context)
{
	t_cmd_node	*cmd_node;

	cmd_node = (t_cmd_node *)node;
	return (ft_dlstforeach_ctx(cmd_node->redirections,
		heredoc_check_callback, context));
}

// static int	create_file(char *filename, char *delimiter, t_shell_context *context)
// {
// 	int	fd;
// 	int	status;

// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return (1);
// 	status = write_file(fd, delimiter, context);
// 	close(fd);
// 	return (status);
// }

// static int	heredoc_check_callback(void *data, void *context_data)
// {
// 	t_redir			*redir;
// 	t_shell_context	*context;
// 	char			*tmp_filename;
// 	char			*delimiter;

// 	redir = (t_redir *)data;
// 	context = (t_shell_context *)context_data;
// 	if (redir->kind != RK_HEREDOC)
// 		return (0);
// 	tmp_filename = gen_filename();
// 	if (!tmp_filename)
// 		return (1);
// 	delimiter = redir->filename;
// 	if (create_file(tmp_filename, delimiter, context) || !ft_dlstpush_back(context->heredoc_files, tmp_filename))
// 	{
// 		unlink(tmp_filename);
// 		free(tmp_filename);
// 		return (1);
// 	}
// 	free(redir->filename);
// 	redir->filename = ft_strdup(tmp_filename);
// 	if (!redir->filename)
// 		return (1);
// 	return (0);
// }

