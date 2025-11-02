#include "expander.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int match_with_pattern(const char *pattern, char *target)
{
	int i;
	int j;

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

static void handle_not_bar(char **new_str, char *pattern)
{
	DIR *dirp;
	struct dirent *dire;
	(void) new_str;
	(void) pattern;

	dirp = opendir(".");
	while (dirp)
	{
		dire = readdir(dirp);
		if (!dire)
			break ;
		if (match_with_pattern(pattern, dire->d_name))
				printf("%s\n", dire->d_name);
	}
	printf("\n");
}

static void	ex_handler_wildcard(t_shell_context *sc, char **new_str, char *pattern)
{
	DIR *dirp;
	struct dirent *dire;

	(void) sc;
	(void) new_str;
	//char *all_dir = str_new("");
	//char **split_bar;
	
	dire = NULL;
	if (!ft_strchr(pattern, '/'))
		handle_not_bar(new_str, pattern);
	else {
		dirp = opendir(pattern);
		closedir(dirp);
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
		if (ft_strchr(*content_split, '*'))
			ex_handler_wildcard(sc, new_str, *content_split);
		content_split++;
	}
}