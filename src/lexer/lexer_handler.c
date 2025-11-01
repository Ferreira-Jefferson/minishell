/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:23:05 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/30 14:38:56 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quotes(const char *input, int *i, char c)
{
	(*i)++;
	while (input[*i] && input[*i] != c)
	{
		if (c == '"' && input[*i] == '\\')
		{
			(*i)++;
			if (!input[*i])
				return (0);
		}
		(*i)++;
	}
	if (input[*i] != c)
		return (0);
	(*i)++;
	return (1);
}

t_token	*handle_word(const char *input, int *i)
{
	int		start;
	char	quotes;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& !ft_strchr("|&<>();", input[*i]))
	{
		if (input[*i] == '\\')
			*i += 1 + (input[*i + 1] != 0);
		else if (input[*i] == '\'' || input[*i] == '"')
		{
			quotes = input[*i];
			if (!skip_quotes(input, i, quotes))
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
				return (NULL);
			}
		}
		else
			(*i)++;
	}
	return (new_token(TK_WORD, ft_substr(input, start, *i - start)));
}

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
