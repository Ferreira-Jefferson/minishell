/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:22:59 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/23 09:49:01 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_dispatch_table(t_token_handler table[])
{
	ft_bzero(table, sizeof(t_token_handler) * 256);
	table['|'] = &handle_pipe;
	table['&'] = &handle_and;
	table[';'] = &handle_list;
	table['('] = &handle_paren;
	table[')'] = &handle_paren;
	table['>'] = &handle_redir;
	table['<'] = &handle_redir;
}

static int	add_token(t_dlist *tokens, t_token *token)
{
	if (!token)
	{
		ft_dlstdestroy(&tokens, free_token);
		return (0);
	}
	if (!ft_dlstpush_back(tokens, token))
	{
		free_token(token);
		ft_dlstdestroy(&tokens, free_token);
		return (0);
	}
	return (1);
}

t_dlist	*tokenize(const char *input, int i)
{
	t_token_handler	table[256];
	t_dlist			*tokens;
	t_token			*token;

	init_dispatch_table(table);
	tokens = ft_dlstinit();
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		if (table[(int) input[i]] != NULL)
			token = table[(int) input[i]](input, &i);
		else
			token = handle_word(input, &i);
		if (!add_token(tokens, token))
			return (NULL);
	}
	token = new_token(TK_EOF, ft_strdup(""));
	if (!add_token(tokens, token))
		return (NULL);
	return (tokens);
}
