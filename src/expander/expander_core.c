/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:30:18 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 15:30:19 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	ex_quotes(char **content)
{
	int	start_quotes;

	start_quotes = 0;
	if (*content && *(content)[0] == '\'' && \
		(*content)[str_len(*content) - 1] == '\'' \
		&& count_quotes(*content, '\'') % 2 == 1)
		start_quotes = 1;
	else if (*content && *(content)[0] == '"' && \
		(*content)[str_len(*content) - 1] == '"' \
		&& count_quotes(*content, '"') % 2 == 1)
		start_quotes = 2;
	if (start_quotes)
	{
		(*content)[str_len(*content) - 1] = '\0';
		(*content)++;
	}
	return (start_quotes);
}

void	ex_tildle(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	char	len;
	size_t	index;

	index = 0;
	while (content[index])
	{
		len = 0;
		if (!start_quotes && content[index] == '~' && \
			content[index + 1] == '\0')
		{
			len = ex_handle_tilde(sc, content, index, new_str);
		}
		else if (!start_quotes && content[index] == '~' && \
			(index == 0 || (index > 0 && ft_isspace(content[index - 1]))))
			len = ex_handle_tilde(sc, content, index, new_str);
		index += len;
		if (len)
			continue ;
		str_tmp[0] = content[index];
		str_tmp[1] = '\0';
		*new_str = str_cat(*new_str, str_tmp);
		index++;
	}
}

void	ex_scape(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	size_t	index;

	(void) sc;
	index = 0;
	while (content[index])
	{
		if (start_quotes != 1 && content[index] == '\\' && content[index + 1])
			if (start_quotes == 0 || \
				(content[index + 1] == '"' || content[index + 1] == '\\' ))
				index++;
		str_tmp[0] = content[index];
		str_tmp[1] = '\0';
		*new_str = str_cat(*new_str, str_tmp);
		index++;
	}
}
