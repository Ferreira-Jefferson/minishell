#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *retorno;
	while (1)
	{
		retorno = readline("minishell> ");
		rl_on_new_line();
		if (!retorno)
		{
			if ()
			break ;
		}
		if (retorno[0] != '\0')
		{
			add_history(retorno);
			if (retorno[0] == 'c' && retorno[1] == 'l' && retorno[2] == 'e' && retorno[3] == 'a'  && retorno[4] == 'r')
				rl_clear_history();

			printf("[%s]\n", retorno);
		}
		free(retorno);
	}
	return (0);
}
