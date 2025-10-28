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

typedef struct s_shell_context t_shell_context;

# include "../lib/libft/include/libft.h"
# include "signals.h"
# include "str.h"
# include "hash_table.h"
# include "utils.h"
# include "lexer.h"
# include "ast.h"
# include "expander.h"


typedef struct s_shell_context
{
	char			*input;
	t_node			*ast_root;		 // Raiz da árvore sintática
	t_hash_table	*env_global;	 // Tabela de variáveis de ambiente
	t_hash_table	*env_copy;		 // Cópia Tabela de variáveis de ambiente
	t_hash_table	*env_local;	     // Variáveis locais (não exportadas)
	char			*cwd;			 // Diretório atual
	char			*last_command;	 // Último comando executado
	int				last_exit_status;// Código de saída do último comando
	int				is_interactive;  // Modo interativo ou script
	int				should_exit;	 // Flag para encerrar o shell
	int				pid_ms;			 // pid do minishell inicial
	int				status;			 // last status code
}   t_shell_context;


t_node *create_complex_test_ast(void);

#endif
