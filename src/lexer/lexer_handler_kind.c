/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_kind.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:29:52 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/15 15:50:06 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_list(const char *input, int *i)
{
	t_token	*token;

	(void) input;
	token = new_token(TK_LIST, ft_strdup(";"));
	(*i)++;
	return (token);
}

t_token	*handle_paren(const char *input, int *i)
{
	t_token	*token;

	if (input[*i] == '(')
		token = new_token(TK_LPAREN, ft_strdup("("));
	else
		token = new_token(TK_RPAREN, ft_strdup(")"));
	(*i)++;
	return (token);
}

t_token	*handle_redir(const char *input, int *i)
{
	t_token	*token;
	char	c;

	c = input[*i];
	if (c == '>' && input[*i + 1] == '>')
		token = new_token(TK_APPEND, ft_strdup(">>"));
	else if (c == '<' && input[*i + 1] && input[*i + 1] == '<')
		token = new_token(TK_HEREDOC, ft_strdup("<<"));
	else if (input[*i] == '>')
		token = new_token(TK_REDIR_OUT, ft_strdup(">"));
	else
		token = new_token(TK_REDIR_IN, ft_strdup("<"));
	if (!token)
		return (NULL);
	*i += ft_strlen(token->lexeme);
	return (token);
}

t_token	*handle_and(const char *input, int *i)
{
	t_token	*token;
	char	c;

	c = input[*i];
	if (c == '&' && input[*i + 1] && input[*i + 1] == '&')
		token = new_token(TK_AND, ft_strdup("&&"));
	else
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '&'", 2);
		(*i)++;
		return (NULL);
	}
	*i += 2;
	return (token);
}

t_token	*handle_pipe(const char *input, int *i)
{
	t_token	*token;
	char	c;

	c = input[*i];
	if (c == '|' && input[*i + 1] && input[*i + 1] == '|')
		token = new_token(TK_OR, ft_strdup("||"));
	else
		token = new_token(TK_PIPE, ft_strdup("|"));
	if (!token)
		return (NULL);
	*i += ft_strlen(token->lexeme);
	return (token);
}
