#ifndef UTILS_H
# define UTILS_H

typedef struct s_node 	t_node;

typedef struct s_shell_context
{
	char			*rl_prompt;
	char			*input;
	t_dlist			*fds;
	t_node			*ast_root;		 // Raiz da árvore sintática
	t_hash_table	*env;	 		 // Tabela de variáveis de ambiente
	t_hash_table	*env_copy;		 // Cópia Tabela de variáveis de ambiente
	char			*pwd;			 // Diretório atual
	char			*last_command;	 // Último comando executado
	int				is_interactive;  // Modo interativo ou script
	int				should_exit;	 // Flag para encerrar o shell
	int				pid_ms;			 // pid do minishell inicial
	t_dlist			*heredoc_files;
	t_dlist			*tokens;
	int				last_status;	 // last status code
}	t_shell_context;

t_hash_table	*env_load(char **envp);
char			*ft_str_toupper(char *str);
void			ft_free_str_vector(char **str_vector);
t_shell_context	*ft_setup_sc(char **envp);
void			ft_define_rl_prompt(t_shell_context	*sc);
char			*ft_create_content(t_dlist	*args);
int				ft_print_error(char *built, char *content, char *message, \
	int status);

	// free_utils.c
int			free_str(char *str, int val);
void		free_arr(char **arr);
int			free_ret(t_dlist **list, void *arg, void (*del)(void *), int ret);
void		free_sc(t_shell_context	*sc);

#endif
