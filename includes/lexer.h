/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:58:07 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/24 11:56:45 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/**
 * @brief Tipos de tokens que o lexer pode gerar.
 *
 * TK_WORD        -> Uma palavra (comando, argumento, nome de arquivo)
 * TK_PIPE        -> |
 * TK_AND         -> &&
 * TK_OR          -> ||
 * TK_LIST        -> ;
 * TK_LPAREN      -> (
 * TK_RPAREN      -> )
 * TK_REDIR_IN    -> <
 * TK_REDIR_OUT   -> >
 * TK_HEREDOC     -> <<
 * TK_APPEND      -> >>
 * TK_EOF         -> Fim da entrada (End of File/Input)
 */
typedef enum e_token_kind
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_LIST,
	TK_LPAREN,
	TK_RPAREN,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}	t_token_kind;

/**
 * @brief Estrutura de um token.
 * @param lexeme O valor literal do token (ex: "echo", "hello world", ">")
 * @param type  O tipo do token, definido pelo enum e_token_type
 */
typedef struct s_token
{
	char			*lexeme;
	t_token_kind	kind;
}	t_token;

typedef t_token *(*t_token_handler)(const char *input, int *i);

t_dlist	*tokenize(const char *input, int i);
t_token	*new_token(t_token_kind kind, char *lexeme);
void	free_token(void *data);
t_token	*handle_list(const char *input, int *i);
t_token	*handle_paren(const char *input, int *i);
t_token	*handle_redir(const char *input, int *i);
t_token	*handle_and(const char *input, int *i);
t_token	*handle_pipe(const char *input, int *i);
t_token	*handle_word(const char *input, int *i);
int		is_operator(t_token *token);
int		is_redirection(t_token_kind kind);
#endif
