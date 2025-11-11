#include "expander.h"

static int	is_valid_pattern(const char *pattern, char *target)
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

int	match_with_pattern(const char *pattern, char *target, int i, int j)
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

char	*handle_not_bar(char *pattern)
{
	DIR				*dirp;
	struct dirent	*dire;
	char			*all_file_name;

	all_file_name = str_new("");
	dirp = opendir(".");
	while (dirp)
	{
		dire = readdir(dirp);
		if (!dire)
			break ;
		if (match_with_pattern(pattern, dire->d_name, 0, 0))
		{
			if (str_len(all_file_name))
				all_file_name = str_cat(all_file_name, "\n");
			all_file_name = str_cat(all_file_name, dire->d_name);
		}
	}
	return (sort_file_name(all_file_name, 0, 0));
}

char	*ex_handler_wildcard(t_shell_context *sc, char *pattern)
{
	DIR				*dirp;
	struct dirent	*dire;

	(void) sc;
	dire = NULL;
	if (!ft_strchr(pattern, '/'))
		return (handle_not_bar(pattern));
	else
	{
		dirp = opendir(pattern);
		closedir(dirp);
		return (NULL);
	}
}

void	ex_wildcard(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	**content_split;
	size_t	i;

	if (start_quotes || ft_strchr(content, '/'))
	{
		*new_str = str_replace(*new_str, content);
		return ;
	}
	remove_duplicated_wildcard(&content);
	content_split = ft_split(content, ' ');
	i = 0;
	while (content_split[i])
	{
		if (str_len(*new_str))
			*new_str = str_cat(*new_str, " ");
		if (ft_strchr(content_split[i], '*'))
			*new_str = str_cat(*new_str, \
				ex_handler_wildcard(sc, content_split[i]));
		else
			*new_str = str_cat(*new_str, content_split[i]);
		i++;
	}
	ft_free_str_vector(content_split);
}
