/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:41:49 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/11 15:16:37 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "../lib/libft/include/libft.h"
# include "signals.h"
# include "str.h"
# include "hash_table.h"
# include "utils.h"
# include "lexer.h"
# include "ast.h"

typedef struct s_node	t_node;

typedef struct s_shell_context
{
	char			*input;
	t_node			*ast_root;		 // Raiz da árvore sintática
	t_hash_table	*env_global;	 // Tabela de variáveis de ambiente
	t_hash_table	*env_copy;		 // Cópia Tabela de variáveis de ambiente
	t_hash_table	*env_local;		 // Variáveis locais (não exportadas)
	char			*cwd;			 // Diretório atual
	char			*last_command;	 // Último comando executado
	int				is_interactive;  // Modo interativo ou script
	int				should_exit;	 // Flag para encerrar o shell
	int				pid_ms;			 // pid do minishell inicial
	int				last_status;	 // last status code
}   t_shell_context;

int		free_str(char *str, int val);
void	free_arr(char **arr);
int		free_ret(t_dlist **list, void *arg, void (*del)(void *), int ret);

#endif
