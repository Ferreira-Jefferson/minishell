#include "minishell.h"

unsigned long	hash_djb2(char *str)
{
	int hash;

	hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) + *str;
	return (hash);
}
