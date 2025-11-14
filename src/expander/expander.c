/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:30:27 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 15:30:48 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	ex_handle_tilde(t_shell_context *sc, char *content, \
	int index, char **new_str)
{
	int		len;
	int		is_valid;
	char	*key;

	len = 2;
	key = NULL;
	is_valid = (content && (content[index + 1] == '\0' || \
		(ft_isspace(content[index + 2]) || content[index + 2] == '/')));
	if (is_valid && content[index + 1] == '+')
		key = ex_get_key(str_new("PWD"));
	else if (is_valid && content[index + 1] == '-')
		key = ex_get_key(str_new("OLDPWD"));
	else if (content[index + 1] == '\0' || content[index + 1] == '/' \
		|| ft_isspace(content[index + 1]))
	{
		key = ex_get_key(str_new("HOME"));
		len = 1;
	}
	if (key == NULL)
		len = 0;
	if (len)
		ex_get_value_variable(sc, new_str, key);
	return (len);
}

void	ex_remove_duplicate_quotes(t_shell_context *sc, char *content, \
	char **new_str)
{
	char	str_tmp[2];
	size_t	index;

	(void) sc;
	index = 0;
	while (content[index])
	{
		if ((content[index] && content[index + 1]) && \
			(content[index] == '"' && content[index + 1] == '"'))
			index += 2;
		else if (index > 0 && content[index] == '"' \
			&& content[index - 1] != '\\')
			index += 1;
		str_tmp[0] = content[index];
		str_tmp[1] = '\0';
		*new_str = str_cat(*new_str, str_tmp);
		if (content[index] == '\0')
			return ;
		index++;
	}
}

int	expander(t_shell_context *sc, t_dnode *node)
{
	char	*new_str;
	char	*content;
	int		start_quotes;

	new_str = str_new("");
	content = node->content;
	start_quotes = ex_quotes(&content);
	ex_tildle(sc, content, &new_str, start_quotes);
	content = str_new(new_str);
	new_str = str_replace(new_str, "");
	ex_vars(sc, content, &new_str, start_quotes);
	content = str_replace(content, new_str);
	new_str = str_replace(new_str, "");
	ex_wildcard(sc, content, &new_str, start_quotes);
	content = str_replace(content, new_str);
	new_str = str_replace(new_str, "");
	ex_remove_duplicate_quotes(sc, content, &new_str);
	content = str_replace(content, new_str);
	new_str = str_replace(new_str, "");
	ex_scape(sc, content, &new_str, start_quotes);
	node->content = ft_strdup(new_str);
	str_free(new_str);
	str_free(content);
	return (0);
}
