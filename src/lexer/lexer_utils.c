/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:20:38 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/22 15:49:33 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*new_token(t_token_kind kind, char *lexeme)
{
	t_token	*token;

	if (!lexeme)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		free(lexeme);
		return (NULL);
	}
	token->kind = kind;
	token->lexeme = lexeme;
	return (token);
}

void	free_token(void *data)
{
	t_token	*token;

	if (!data)
		return ;
	token = (t_token *) data;
	if (token->lexeme)
		free(token->lexeme);
	free(token);
}
