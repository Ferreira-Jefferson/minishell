#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_shell_context	sc;
	//char			*input;

	(void)argc;
	(void)argv;

	t_dnode *node = malloc(sizeof(t_dnode));
	node->content = str_new("teste ~ $~ ~$ ~+N ~-N A~ ~A A~A ~+/foo ~-/bar $$ $? $VA $USR");
	printf("Antes:[%s]\n", (char *)node->content);
	sc.pid_ms = getpid();
	//sc.ast_root = create_complex_test_ast();
	sc.status = 0;
	sc.env_local = NULL;
	sc.env_global = env_load(envp);
	sc.env_copy = env_load(envp);

	expander(&sc, node);
	printf("Depois:[%s]\n", (char *)node->content);
	str_free(node->content);
	free(node);
	ht_free(sc.env_global);
	ht_free(sc.env_copy);
	return 0;

	// ht_print(sc.env_global);	
	// while (1)
	// {
	// 	input = readline("minishell~$ ");
	// 	if (!input && get_g_signal_status() == 0)
	// 	{
	// 		write(1, "exit\n", 5);
	// 		break ;
	// 	}
	// 	if (input[0] != '\0')
	// 		add_history(input);
	// 	sc.input = input;
	// 	// expander(&sc);
	// 	free(input);
	// }
	// ht_free(sc.env_global);
	// return (0);
}
