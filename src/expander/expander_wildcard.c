#include "expander.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

char	*ft_str_toupper(char *str)
{
	char *aux;
	int	i;

	i = 0;
	aux = str_new(str);
	while (aux[i])
	{
		aux[i] = ft_toupper(aux[i]);
		i++;
	}
	return (aux);
}

void	ft_free_str_vector(char **str_vector)
{
	char	**aux;

	aux = str_vector;
	while (*aux)
	{
		free(*aux);
		aux++;
	}
	free(str_vector);
}

char *join_file_name(char **split, char *all_file_name)
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

int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int asterisk_in_start(char *str)
{
	int k;

	k = 0;
	while (str[k] == '*')
		k++;
	return (k);
}

char *sort_file_name(char *all_file_name)
{
	char **split = ft_split(all_file_name, '\n');
	int i;
	int j;

	char *tmp;

	i = 0;
	while (split[i])
	{
		j = i + 1;
		while (split[j])
		{
			if (ft_strcmp(ft_str_toupper(split[i]) + asterisk_in_start(split[i])
			, ft_str_toupper(split[j]) + asterisk_in_start(split[j])) > 0)
			{
				tmp = split[i];
				split[i] = split[j];
				split[j] = tmp;
			}
			j++;
		}
		i++;
	}
	if (split[0])
		all_file_name = join_file_name(split, all_file_name);
	ft_free_str_vector(split);
	return (all_file_name);
}

int match_with_pattern(const char *pattern, char *target)
{
	int i;
	int j;

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
	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*')
		{
			i++;
			while (target[j] && target[j] != pattern[i])
				j++;
			if (!target[j] && pattern[i + 1])
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

char *handle_not_bar(char *pattern)
{
	DIR *dirp;
	struct dirent *dire;
	char *all_file_name;

	all_file_name = str_new("");
	dirp = opendir(".");
	while (dirp)
	{
		dire = readdir(dirp);
		if (!dire)
			break ;
		if (match_with_pattern(pattern, dire->d_name))
		{
			if (str_len(all_file_name))
				all_file_name = str_cat(all_file_name, "\n");
			all_file_name = str_cat(all_file_name, dire->d_name);
		}
	}
	return (sort_file_name(all_file_name));
}

char *ex_handler_wildcard(t_shell_context *sc, char *pattern)
{
	DIR *dirp;
	struct dirent *dire;

	(void) sc;

	dire = NULL;
	if (!ft_strchr(pattern, '/'))
		return (handle_not_bar(pattern));
	else {
		dirp = opendir(pattern);
		closedir(dirp);
		return (NULL);
	}
}

static void	remove_duplicated_wildcard(char **content)
{
	int i;
	int j;
	char *new_str = malloc(str_len(*content));

	i = 0;
	j = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '*' && ((content + i + 1) && (*content)[i + 1] == '*'))
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
		*content = str_replace(*content, new_str);
	free(new_str);
}

void	ex_wildcard(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	size_t	index;

	(void) sc;
	(void) start_quotes;
	(void) str_tmp;
	(void) index;

	index = 0;
	remove_duplicated_wildcard(&content);
	char **content_split = ft_split(content, ' ');
	while (*content_split)
	{
		if (str_len(*new_str))
			*new_str = str_cat(*new_str, " ");
		if (ft_strchr(*content_split, '*'))
			*new_str = str_cat(*new_str, ex_handler_wildcard(sc, *content_split));
		else
			*new_str = str_cat(*new_str, *content_split);
		content_split++;
	}
}