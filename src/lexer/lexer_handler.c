/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:23:05 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/14 15:29:44 by jtertuli         ###   ########.fr       */
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
