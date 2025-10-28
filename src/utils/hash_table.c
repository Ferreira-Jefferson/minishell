#include "minishell.h"

t_hash_table	*ht_create(void)
{
	t_hash_table	*table;

	table = malloc(sizeof(t_hash_table));
	if (!table)
		return (NULL);
	table->size = INITIAL_SIZE;
	table->items = (t_env_item **) ft_calloc(table->size, sizeof(t_env_item *));
	if (!table->items)
	{
		free(table);
		return (NULL);
	}
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

char	*ht_search(t_hash_table *table, char *key)
{
	t_env_item	*env_item;
	size_t		index;

	if (!table || !key)
		return (NULL);
	index = hash_djb2(key) % table->size;
	env_item = table->items[index];
	while (env_item)
	{
		if (ft_strncmp(env_item->key, key, ft_strlen(key)) == 0)
			return (str_new(env_item->value));
		env_item = env_item->next;
	}
	return (NULL);
}

static void	ht_free_item(t_env_item *env_item)
{
	str_free(env_item->key);
	str_free(env_item->value);
	free(env_item);
}

void	ht_delete(t_hash_table *table, char *key)
{
	t_env_item	*env_item;
	t_env_item	*before;
	size_t		index;

	index = hash_djb2(key) % table->size;
	env_item = table->items[index];
	if (!env_item)
		return ;
	if (ft_strncmp(env_item->key, key, ft_strlen(key)) == 0)
	{
		table->items[index] = env_item->next;
		return (ht_free_item(env_item));
	}
	before = env_item;
	env_item = env_item->next;
	while (env_item)
	{
		if (ft_strncmp(env_item->key, key, ft_strlen(key)) == 0)
		{
			before->next = env_item->next;
			return (ht_free_item(env_item));
		}
		before = env_item;
		env_item = env_item->next;
	}
}
