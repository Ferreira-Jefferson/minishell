/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:30:15 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/15 10:24:29 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	match_with_pattern(const char *pattern, char *target, int i, int j)
{
	if (!is_valid_pattern(pattern, target))
		return (0);
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			i++;
			while (target[j] && target[j] != pattern[i])
				j++;
			if (!target[j] && (pattern[i] && pattern[i + 1]))
				return (0);
			while (target[j] && pattern[i] && pattern[i] != '*')
				if (target[j++] != pattern[i++])
					return (0);
		}
		else
		{
			if (target[j] != pattern[i])
				return (0);
			i++;
			j++;
		}
	}
	return (1);
}

static char	*ex_handler_wildcard(char *dir, char *pattern, int has_bar)
{
	DIR				*dirp;
	struct dirent	*dire;
	char			*all_file_name;

	all_file_name = str_new("");
	dirp = opendir(dir);
	while (dirp)
	{
		dire = readdir(dirp);
		if (!dire)
			break ;
		if (match_with_pattern(pattern, dire->d_name, 0, 0))
		{
			if (str_len(all_file_name))
				all_file_name = str_cat(all_file_name, "\n");
			if (has_bar)
			{
				all_file_name = str_cat(all_file_name, dir);
				all_file_name = str_cat(all_file_name, "/");
			}
			all_file_name = str_cat(all_file_name, dire->d_name);
		}
	}
	closedir(dirp);
	return (sort_file_name(all_file_name, 0, 0));
}

static void	ex_handle_sub_wildcard(char *prefix, char *content_aux, \
	char *split_bar_one, char **result)
{
	char	*ex_prefix;
	char	**split_prefix;
	char	*partial;
	int		i;

	ex_prefix = ex_handler_wildcard(".", prefix, 0);
	split_prefix = ft_split(ex_prefix, ' ');
	if (!split_prefix)
		return ;
	i = 0;
	while (split_prefix[i])
	{
		content_aux = str_replace(content_aux, split_bar_one);
		partial = ex_handler_wildcard(split_prefix[i], split_bar_one, 1);
		*result = str_cat(*result, partial);
		str_free(partial);
		i++;
	}
	str_free(content_aux);
	str_free(ex_prefix);
	free_arr(split_prefix);
}

static void	ex_list_paths(char **split_bar, char **new_str, char *content_aux)
{
	char	*prefix;
	char	*result;

	result = str_new("");
	prefix = str_new("");
	if (!split_bar[1])
		result = ex_handler_wildcard(".", split_bar[0], 0);
	else if (!split_bar[2])
	{
		prefix = str_cat(prefix, split_bar[0]);
		if (ft_strchr(prefix, '*'))
			ex_handle_sub_wildcard(prefix, content_aux, split_bar[1], &result);
		else
		{
			content_aux = str_replace(content_aux, split_bar[1]);
			result = str_cat(result, \
				ex_handler_wildcard(prefix, split_bar[1], 1));
		}
	}
	*new_str = str_cat(*new_str, result);
	str_free(prefix);
	str_free(result);
}

void	ex_wildcard(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	*content_aux;
	char	**split_bar;

	(void) sc;
	if (start_quotes || !ft_strchr(content, '*'))
	{
		*new_str = str_cat(*new_str, content);
		return ;
	}
	content_aux = str_new(content);
	remove_duplicated_wildcard(&content_aux);
	split_bar = ft_split(content_aux, '/');
	if (!split_bar)
		return ;
	ex_list_paths(split_bar, new_str, content_aux);
	if (str_len(*new_str) == 0)
		*new_str = str_cat(*new_str, content);
	free_arr(split_bar);
}
