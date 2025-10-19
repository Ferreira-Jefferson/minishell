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
		if (!retorno)
			break ;
		if (retorno[0] != '\0')
		{
			add_history(retorno);
			printf("[%s]\n", retorno);
		}
		free(retorno);
	}
	return (0);
}
