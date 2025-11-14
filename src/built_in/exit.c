/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:08:12 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 18:19:12 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_validate(t_shell_context *sc, t_dlist *args, int status)
{
	t_dnode	*node;
	char	*to_free;
	char	**split;

	node = ft_dlstnew("");
	node->content = ft_create_content(args);
	to_free = node->content;
	expander(sc, node);
	split = ft_split(node->content, ' ');
	if (!split)
		status = sc->last_status;
	else
	{
		to_free = str_replace(to_free, "numeric argument required");
		if (split[0] && !ft_is_numeric(split[0]))
			status = ft_print_error(sc, split[0], to_free, 2);
		else if (split[1])
			status = ft_print_error(sc, "", "too many arguments", 1);
		else
			status = ft_atoi(split[0]) % 256;
	}
	str_free(to_free);
	ft_free_str_vector(split);
	ft_dlstdelone(node, free);
	return (status);
}

int	b_exit(t_shell_context *sc, t_dlist	*args, int print)
{
	int	status;

	sc->cmd = str_replace(sc->cmd, "exit:");
	if (!args)
		status = sc->last_status;
	else
	{
		ft_dlstremove_at(args, 0, free);
		if (args->size == 0)
			status = sc->last_status;
		else
			status = ft_validate(sc, args, 0);
	}
	free_sc(sc);
	if (print)
		printf("exit\n");
	exit(status);
	return (1);
}
