#include "minishell.h"
#include <stdio.h>

int	main(void)
{
	char *str = str_new("");
	printf("%s\n", str);
	printf("%zu\n", str_len(str));

	str = str_cat(str, 0);
	printf("%s\n", str);
	printf("%zu\n", str_len(str));

	str_free(str);
	return (0);
}