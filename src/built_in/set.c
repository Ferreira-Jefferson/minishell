#include "built_in.h"

static void	set_var(t_shell_context *sc, char **split)
{
	char	*content;
	char	**split_set;

	while (*split)
	{
		content = str_new(*split);
		split_set = ft_split(content, '=');
		if (ft_strchr(content, '='))
		{
			if (split_set[1] == NULL)
				ht_update_insert(sc->env, split_set[0], "", (t_env_type) EXPORT);
			else
				ht_update_insert(sc->env, split_set[0], split_set[1], (t_env_type) EXPORT);
		}
		str_free(content);
		ft_free_str_vector(split_set);
		split++;
	}
}

char *validate_set(char **split)
{
	while (*split)
	{
		if (!ft_strchr(*split, '='))
			return (str_new(*split));
		split++;
	}
	return (NULL);
}

int	b_set(t_shell_context *sc, char **content)
{
	char *ret;
	char *tmp;

	if (!content)
		return (0);
	ret = validate_set(content);
	if (ret != NULL)
	{
		tmp = content[0];
		content[0] = str_clear(content[0]);
		content[0] = str_cat(content[0], ret);
		content[1] = str_clear(content[1]);
		content[1] = str_cat(content[1], tmp);
		str_free(ret);
		return (1);
	}
	set_var(sc, content);
	exit (0);
	return (0);
}
