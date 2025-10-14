#include "../includes/minishell.h"
#include <stdio.h>

int	main(void)
{
	char *str = str_new("teste");
	printf("%s\n", str);
	printf("%zu\n", str_len(str));

	str = str_cat(str, " um complemento maior");
	printf("%s\n", str);
	printf("%zu\n", str_len(str));

	str_free(str);
	return (0);
}