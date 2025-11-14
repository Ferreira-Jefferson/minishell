/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:07:07 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 09:07:47 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	print_env(t_env_item *env_item, char **str_env)
{
	while (env_item)
	{
		if (str_len(*str_env) > 0 && (env_item + 1))
			*str_env = str_cat(*str_env, "\n");
		*str_env = str_cat(*str_env, env_item->key);
		*str_env = str_cat(*str_env, "=");
		*str_env = str_cat(*str_env, env_item->value);
		env_item = env_item->next;
	}
	free(env_item);
}

int	ft_validate_env(t_shell_context *sc, t_dlist *args)
{
	t_dnode	*node;
	char	*content;
	int		status;

	if (!args)
		return (0);
	ft_dlstremove_at(args, 0, free);
	if (!args || args->size == 0)
		return (0);
	node = ft_dlstnew(args->head->content);
	expander(sc, node);
	content = str_new("‘");
	content = str_cat(content, node->content);
	content = str_cat(content, "’");
	status = ft_print_error("env:", content, "No such file or directory", 127);
	str_free(content);
	return (status);
}

int	b_env(t_shell_context *sc, t_dlist *args)
{
	t_hash_table	*table;
	t_env_item		*env_item;
	char			*str_env;
	int				i;

	if (ft_validate_env(sc, args))
		return (sc->last_status);
	str_env = str_new("");
	table = sc->env;
	if (!table)
		return (1);
	i = 0;
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			if (env_item->type == ENV || \
				(env_item->type == EXPORT && env_item->value != NULL))
				print_env(env_item, &str_env);
		}
		i++;
	}
	printf("%s\n", str_env);
	return (0);
}
