#ifndef UTILS_H
# define UTILS_H

typedef struct s_shell_context
{
	char			*input;
	t_node			*ast_root;		 // Raiz da árvore sintática
	t_hash_table	*env;	 		// Tabela de variáveis de ambiente
	t_hash_table	*env_copy;		 // Cópia Tabela de variáveis de ambiente
	char			*pwd;			 // Diretório atual
	char			*last_command;	 // Último comando executado
	int				is_interactive;  // Modo interativo ou script
	int				should_exit;	 // Flag para encerrar o shell
	int				pid_ms;			 // pid do minishell inicial
	int				last_status;	 // last status code
}   t_shell_context;

t_hash_table	*env_load(char **envp);
char			*ft_str_toupper(char *str);
void			ft_free_str_vector(char **str_vector);
t_shell_context	*ft_setup_sc(char **envp);
void			free_sc(t_shell_context	*sc);

#endif