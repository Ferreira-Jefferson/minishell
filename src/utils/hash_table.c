/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:17:53 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/13 13:15:37 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ht_insert(t_hash_table *table, char *key, char *value, t_env_type type)
{
	t_env_item		*env_item;
	size_t			index;
	char			*search_value;

	env_item = (t_env_item *) malloc(sizeof(t_env_item));
	if (!env_item)
		return ;
	search_value = ht_search(table, key);
	if (search_value && value == NULL)
	{
		free(env_item);
		str_free(search_value);
		return ;
	}
	env_item->key = str_new(key);
	env_item->value = str_new(value);
	env_item->type = type;
	index = hash_djb2(key) % table->size;
	env_item->next = table->items[index];
	table->items[index] = env_item;
	if (search_value)
		str_free(search_value);
}

char	*ht_search(t_hash_table *table, char *key)
{
	t_env_item	*env_item;
	size_t		index;

	if (!table)
		return (NULL);
	index = hash_djb2(key) % table->size;
	env_item = table->items[index];
	while (env_item)
	{
		if (ft_strcmp(env_item->key, key) == 0)
			return (str_new(env_item->value));
		env_item = env_item->next;
	}
	return (NULL);
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
	if (ft_strcmp(env_item->key, key) == 0)
	{
		table->items[index] = env_item->next;
		return (ht_free_item(env_item));
	}
	before = env_item;
	env_item = env_item->next;
	while (env_item)
	{
		if (ft_strcmp(env_item->key, key) == 0)
		{
			before->next = env_item->next;
			return (ht_free_item(env_item));
		}
		before = env_item;
		env_item = env_item->next;
	}
}

void	ht_update_insert(t_hash_table *table, char *key, char *value, \
	t_env_type type)
{
	size_t		index;
	t_env_item	*item;

	if (!table || !key)
		return ;
	index = hash_djb2(key) % table->size;
	item = table->items[index];
	while (item)
	{
		if (ft_strcmp(item->key, key) == 0)
		{
			if (value)
				item->value = str_replace(item->value, value);
			return ;
		}
		item = item->next;
	}
	ht_insert(table, key, value, type);
}
