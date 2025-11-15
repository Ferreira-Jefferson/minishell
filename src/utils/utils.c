/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:07:36 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/15 10:27:09 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_table	*env_load(char **envp)
{
	t_hash_table	*table;
	char			*key;
	char			*value;
	char			*first_equal;

	table = ht_create();
	if (!table)
		return (NULL);
	while (*envp)
	{
		first_equal = ft_strchr(*envp, '=');
		if (first_equal)
		{
			key = malloc(first_equal - *envp + 1);
			if (!key)
				return (NULL);
			ft_strlcpy(key, *envp, first_equal - *envp + 1);
			value = ft_strdup(first_equal + 1);
			ht_insert(table, key, value, (t_env_type) ENV);
			free(key);
			free(value);
		}
		envp++;
	}
	return (table);
}

char	*ft_str_toupper(char *str)
{
	int		i;
	char	*str_aux;

	str_aux = str_new(str);
	i = 0;
	while (str_aux[i])
	{
		str_aux[i] = ft_toupper(str_aux[i]);
		i++;
	}
	return (str_aux);
}

char	*ft_create_content(t_dlist	*args)
{
	char	*content;
	t_dnode	*node;
	t_dnode	*head;

	if (!args)
		return (NULL);
	head = args->head;
	node = args->head;
	content = str_new("");
	while (node)
	{
		content = str_cat(content, node->content);
		if (node->next)
			content = str_cat(content, " ");
		node = node->next;
	}
	args->head = head;
	return (content);
}

int	ft_print_error(t_shell_context *sc, char *content, \
	char *message, int status)
{
	char	*output;

	sc->last_status = status;
	output = str_new("bash: ");
	output = str_cat(output, sc->cmd);
	output = str_cat(output, " ");
	output = str_cat(output, content);
	if (*content)
		output = str_cat(output, ": ");
	output = str_cat(output, message);
	output = str_cat(output, "\n");
	ft_putstr_fd(output, 2);
	str_free(output);
	return (status);
}

char	*remove_chars(char *str, char *set)
{
	char	*src;
	char	*dest;

	if (!str || !set)
		return (NULL);
	src = str;
	dest = str;
	while (*src)
	{
		if (!ft_strchr(set, *src))
			*dest++ = *src;
		src++;
	}
	*dest = '\0';
	return (str);
}
