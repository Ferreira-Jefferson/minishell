#include "minishell.h"

t_hash_table	*ht_create(void)
{
	t_hash_table	*table;

	table = (t_hash_table *) malloc(sizeof(t_hash_table *));
	if (!table)
		return (NULL);
	table->size = INITIAL_SIZE;
	table->items = (t_env_item **) ft_calloc(table->size, sizeof(t_env_item *));
	if (!table->size)
		return (NULL);
	return (table);
}

void	ht_insert(t_hash_table *table, char *key, char *value)
{
	t_env_item		*env_item;
	size_t			index;

	env_item = (t_env_item *) malloc(sizeof(t_env_item));
	if (!env_item)
		return ;
	env_item->key = str_new(key);
	env_item->value = str_new(value);
	index = hash_djb2(key) % table->size;
	env_item->next = table->items[index];
	table->items[index] = env_item;
}

char	*ht_search(t_hash_table  *table,  char  *key)
{
	t_env_item	*env_item;
	size_t		index;

	index = hash_djb2(key) % table->size;
	env_item = table->items[index];
	while (env_item)
	{
		if (ft_isequal(env_item->key, key))
			return (env_item->value);
		env_item = env_item->next;
	}
	return (NULL);
}

void	ht_free_item(t_env_item *env_item)
{
	str_free(env_item->key);
	str_free(env_item->value);
	free(env_item);
}

void	ht_delete(t_hash_table  *table,  char *key)
{
	t_env_item *env_item;
	t_env_item *before;
	size_t		index;

	index = hash_djb2(key) % table->size;
	env_item = table->items[index];
	if (!env_item)
		return ;
	if (ft_isequal(env_item->key, key))
	{
		table->items[index] = env_item->next;
		return (ht_free_item(env_item));
	}
	before = env_item;
	env_item = env_item->next;
	while(env_item)
	{
		if (ft_isequal(env_item->key, key))
		{
			before->next = env_item->next;
			return (ht_free_item(env_item));
		}
		before = env_item;
		env_item = env_item->next;
	}
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
				ht_free_item(to_free);
			}
		}
		i++;
	}
	free(table->items);
	free(table);
}


