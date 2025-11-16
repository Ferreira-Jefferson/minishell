/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:07:03 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/16 09:13:01 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	handle_set(t_shell_context *sc, t_dnode	*node, char **split)
{
	if (!split)
		return (-1);
	if (!ft_isvalid_key(split[0]))
	{
		if (split[0][0] != '#')
			printf("bash: export: '%s': not a valid identifier\n", split[0]);
		return (-1);
	}
	if (ft_strchr(node->content, '='))
	{
		if (split[1] == NULL)
			ht_update_insert(sc->env, split[0], "", (t_env_type) EXPORT);
		else
			ht_update_insert(sc->env, split[0], split[1], (t_env_type) EXPORT);
	}
	else
		ht_insert(sc->env, split[0], NULL, (t_env_type) EXPORT);
	return (0);
}

static void	set_var(t_shell_context *sc, t_dlist *args)
{
	t_dnode	*cur;
	t_dnode	*next;
	char	**split;
	int		ret;
	char	*copy;

	cur = args->head;
	while (cur)
	{
		next = cur->next;
		copy = str_new(cur->content);
		split = ft_split(copy, '=');
		ret = handle_set(sc, cur, split);
		str_free(copy);
		free_arr(split);
		ft_dlstremove_node(args, cur, free);
		if (ret == -1)
			return ;
		cur = next;
	}
}

int	b_set_export(t_shell_context *sc, t_dlist	*args)
{
	char	**split;

	if (!args || !args->head)
		return (1);
	split = ft_split(args->head->content, '=');
	if (!split)
		return (1);
	if (split[0][0] == '#')
	{
		free_arr(split);
		return (b_export(sc, args));
	}
	free_arr(split);
	set_var(sc, args);
	return (0);
}
