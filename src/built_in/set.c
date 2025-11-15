/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:06:56 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/15 10:24:29 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	set_var(t_shell_context *sc, char **split)
{
	char	*content;
	char	**split_set;

	while (*split)
	{
		content = str_new(*split);
		split_set = ft_split(content, '=');
		if (ft_strchr(content, '='))
		{
			if (split_set[1] == NULL)
				ht_update_insert(sc->env, split_set[0], "", \
					(t_env_type) SET);
			else
				ht_update_insert(sc->env, split_set[0], split_set[1], \
					(t_env_type) SET);
		}
		str_free(content);
		free_arr(split_set);
		split++;
	}
}

char	*validate_set(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (!ft_strchr(split[i], '='))
			return (split[i]);
		i++;
	}
	return (NULL);
}

static void	ft_handler_cmd_not_found(t_dlist *args, char *ret, \
	char	**content_split)
{
	char	*to_free;

	if (args->size > 1)
	{
		if (args->head)
		{
			to_free = args->head->content;
			args->head->content = ft_strdup(ret);
			free(to_free);
		}
	}
	free_arr(content_split);
}

int	b_set(t_shell_context *sc, t_dlist *args)
{
	char	*ret;
	t_dnode	*node;
	char	**content_split;
	char	*content;

	if (!args || args->size == 0)
		return (1);
	content = ft_create_content(args);
	node = ft_dlstnew(content);
	expander(sc, node);
	content_split = ft_split(node->content, ' ');
	str_free(content);
	ft_dlstdelone(node, free);
	ret = validate_set(content_split);
	if (ret != NULL)
	{
		ft_handler_cmd_not_found(args, ret, content_split);
		return (1);
	}
	set_var(sc, content_split);
	free_arr(content_split);
	return (0);
}
