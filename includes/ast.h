/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:53:59 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/28 08:42:31 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "ast.h"
# include "../lib/libft/include/libft.h"

/**
 * @brief Tipos de nós da AST
 *
 * NK_COMMAND  -> comando simples (ex: ls, echo, cd, etc)
 * NK_PIPE     -> operador |   (conecta stdout -> stdin)
 * NK_LIST     -> operador ;   (executa comandos em sequência)
 * NK_AND      -> operador &&  (executa o próximo se o anterior teve sucesso)
 * NK_OR       -> operador ||  (executa o próximo se o anterior falhar)
 * NK_SUBSHELL -> comandos entre parênteses
 */

typedef enum e_node_kind
{
	NK_COMMAND,
	NK_PIPE,
	NK_LIST,
	NK_AND,
	NK_OR,
	NK_SUBSHELL
}	t_node_kind;

typedef enum e_redir_kind
{
	RK_INPUT,
	RK_OUTPUT,
	RK_HEREDOC,
	RK_APPEND
}	t_redir_kind;

typedef struct s_redir
{
	t_redir_kind	kind;
	char			*filename;
	int				target_fd;
}	t_redir;

typedef struct s_node
{
	t_node_kind	kind;
}	t_node;

typedef struct s_cmd_node
{
	t_node	base;
	t_dlist	*args;
	t_dlist	*redirections;
}	t_cmd_node;

typedef struct s_bin_node
{
	t_node	base;
	t_node	*left;
	t_node	*right;
}	t_bin_node;

typedef struct s_pipe_node
{
	t_node	base;
	t_dlist	*commands;
}	t_pipe_node;

typedef struct s_sub_node
{
	t_node	base;
	t_node	*sub_ast;
}	t_sub_node;

#endif