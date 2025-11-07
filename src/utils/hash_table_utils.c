#include "minishell.h"

unsigned long	hash_djb2(char *str)
{
	int	hash;

	hash = 5381;
	while (*str)
	{
		hash = ((hash << 5) + hash) + *str;
		str++;
	}
	return (hash);
}
void	ht_free_item(t_env_item *env_item)
{
	str_free(env_item->key);
	str_free(env_item->value);
	free(env_item);
}

void	ht_free(t_hash_table *table)
{
	int			i;
	t_env_item	*env_item;
	t_env_item	*to_free;

	if (!table)
		return ;
	i = 0;
	while (i < table->size)
	{
		env_item = table->items[i];
		while (env_item)
		{
			to_free = env_item;
			str_free(to_free->key);
			str_free(to_free->value);
			env_item = to_free->next;
			free(to_free);
		}
		i++;
	}
	free(table->items);
	free(table);
}

void	ht_print(t_hash_table *table)
{
	int			i;
	t_env_item	*env_item;

	if (!table)
		return ;
	i = 0;
	i = 0;
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			while (env_item)
			{
				printf("[%d]: {%s: %s}\n", i, env_item->key, env_item->value);
				env_item = env_item->next;
			}
			free(env_item);
		}
		i++;
	}
}
