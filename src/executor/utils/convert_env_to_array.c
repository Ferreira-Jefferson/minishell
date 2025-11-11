/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:25:54 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 18:14:57 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	count_items(t_hash_table *hash_items)
{
	int	i;
	int	count;
	t_env_item	*curr;

	i = 0;
	count = 0;
	while (i < hash_items->size)
	{
		curr = hash_items->items[i];
		while (curr)
		{
			count++;
			curr = curr->next;
		}
		i++;
	}
	return (count);
}

static int	parse_env(t_hash_table *hash_items, char **envp)
{
	t_env_item	*item;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < hash_items->size)
	{
		item = hash_items->items[i];
		while (item)
		{
			envp[j] = ft_strjoinv(NULL, 3, item->key, "=", item->value);
			if (!envp[j])
				return (1);
			j++;
			item = item->next;
		}
		i++;
	}
	return (0);
}

char	**convert_env_to_array(t_hash_table *hash_items)
{
	char	**envp;
	int		count;

	count = count_items(hash_items);
	envp = ft_calloc(count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	if (parse_env(hash_items, envp))
	{
		free_arr(envp);
		return (NULL);
	}
	return (envp);
}
