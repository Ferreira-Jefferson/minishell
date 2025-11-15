/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:08:00 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 15:24:20 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*fake_expander(t_shell_context *context, char *str)
{
	t_dnode	*fake_node;
	char	*aux;
	char	*expanded_str;
	char	*final_str;

	fake_node = ft_dlstnew(NULL);
	if (!fake_node)
		return (NULL);
	fake_node->content = ft_strdup(str);
	if (!fake_node->content)
	{
		ft_dlstdelone(fake_node, NULL);
		return (NULL);
	}
	aux = (char *)fake_node->content;
	expander(context, fake_node);
	expanded_str = (char *)fake_node->content;
	final_str = ft_strdup(expanded_str);
	free(aux);
	free(expanded_str);
	ft_dlstdelone(fake_node, NULL);
	if (!final_str)
		return (NULL);
	return (remove_chars(final_str, "\'\""));
}
