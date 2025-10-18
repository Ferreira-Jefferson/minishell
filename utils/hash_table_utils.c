#include "minishell.h"

unsigned long	hash_djb2(char *str)
{
	int hash;

	hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) + *str;
	return (hash);
}

void	ht_free(t_hash_table  *table)
{
	int	i;
	t_env_item *env_item;
	t_env_item *to_free;

	if (!table)
		return ;
	i = 0;
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			while (env_item)
			{
				to_free = env_item;
				env_item = env_item->next;
				str_free(to_free->key);
				str_free(to_free->value);
				free(to_free);
			}
		}
		i++;
	}
	free(table->items);
	free(table);
}
