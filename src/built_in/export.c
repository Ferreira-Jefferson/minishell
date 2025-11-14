/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:08:07 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 15:14:37 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	create_export_list(t_env_item *env_item, char **str_env)
{
	while (env_item)
	{
		if (str_len(*str_env) > 0 && (env_item + 1))
			*str_env = str_cat(*str_env, "\n");
		*str_env = str_cat(*str_env, "declare -x ");
		*str_env = str_cat(*str_env, env_item->key);
		if (env_item->value != NULL)
		{
			*str_env = str_cat(*str_env, "=");
			*str_env = str_cat(*str_env, "\"");
			*str_env = str_cat(*str_env, env_item->value);
			*str_env = str_cat(*str_env, "\"");
		}
		env_item = env_item->next;
	}
	free(env_item);
}

static int	print_export(t_shell_context *sc, int i)
{
	char			*str_env;
	char			*sorted;
	t_env_item		*env_item;
	t_hash_table	*table;

	str_env = str_new("");
	table = sc->env;
	if (!table)
		return (1);
	while (i < table->size)
	{
		if (table->items[i])
		{
			if (table->items[i]->type != SET)
			{
				env_item = table->items[i];
				create_export_list(env_item, &str_env);
			}
		}
		i++;
	}
	sorted = sort_export(str_env);
	printf("%s", sorted);
	str_free(sorted);
	return (0);
}

int	b_export(t_shell_context *sc, t_dlist *args)
{
	(void) args;
	ft_dlstremove_at(args, 0, free);
	if (args->size == 0)
		return (print_export(sc, 0));
	return (0);
}
