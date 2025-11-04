#include "built_in.h"

static char	*join_str_export(char **split, char *str_export_split)
{
	str_export_split = str_replace(str_export_split, "");
	while (*split)
	{
		if (str_len(str_export_split) > 0)
			str_export_split = str_cat(str_export_split, " ");
		str_export_split = str_cat(str_export_split, *split);
		str_export_split = str_cat(str_export_split, "\n");
		split++;
	}
	return (str_export_split);
}

char	*sort_export(char *str_export, int i, int j)
{
	char	**split;
	char	*tmp;

	split = ft_split(str_export, '\n');
	while (split[i])
	{
		j = i + 1;
		while (split[j])
		{
			if (ft_strcmp(ft_str_toupper(split[i]), ft_str_toupper(split[j])) > 0)
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
		str_export = join_str_export(split, str_export);
	ft_free_str_vector(split);
	return (str_export);
}
