/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:30:11 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 15:56:08 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*join_file_name(char **split, char *all_file_name)
{
	all_file_name = str_replace(all_file_name, "");
	while (*split)
	{
		if (str_len(all_file_name) > 0)
			all_file_name = str_cat(all_file_name, " ");
		all_file_name = str_cat(all_file_name, *split);
		split++;
	}
	return (all_file_name);
}

int	wild_in_start(char *str)
{
	int	k;

	k = 0;
	while (str[k] == '*')
		k++;
	return (k);
}

void	remove_duplicated_wildcard(char **content)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(str_len(*content) + 1);
	i = 0;
	j = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '*' && ((content + i + 1) && \
			(*content)[i + 1] == '*'))
		{
			i++;
			continue ;
		}
		new_str[j] = (*content)[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	if (*content)
		*content = str_cat(str_clear(*content), new_str);
	free(new_str);
}

int	is_valid_pattern(const char *pattern, char *target)
{
	if (ft_strcmp((char *)pattern, "*") == 0 && target[0] != '.')
		return (1);
	if (pattern[0] != '*' && pattern[0] != target[0])
		return (0);
	if (pattern[ft_strlen(pattern) - 1] != '*' && \
		pattern[ft_strlen(pattern) - 1] != target[ft_strlen(target) - 1])
		return (0);
	if (pattern[0] != '.' && target[0] == '.')
		return (0);
	if (pattern[0] == '.' && target[0] != '.')
		return (0);
	return (1);
}
