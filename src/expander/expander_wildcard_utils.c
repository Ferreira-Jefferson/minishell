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

char	*sort_file_name(char *all_file_name, int i, int j)
{
	char	**split;
	char	*tmp;

	split = ft_split(all_file_name, '\n');
	while (split[i])
	{
		j = i + 1;
		while (split[j])
		{
			if (ft_strcmp(ft_str_toupper(split[i]) + wild_in_start(split[i]), \
				ft_str_toupper(split[j]) + wild_in_start(split[j])) > 0)
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