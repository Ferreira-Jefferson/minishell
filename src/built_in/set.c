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
			return (*split);
		split++;
	}
	return (NULL);
}

int	b_set(t_shell_context *sc, t_dlist *args)
{
	char *ret;
	t_dnode	*node;
	char	**content;
	char	*to_free;

	if (!args || args->size == 0)
		return (1);
	node = ft_dlstnew("");
	node->content = ft_create_content(args);
	to_free = node->content;
	expander(sc, node);
	str_free(to_free);
	content = ft_split(node->content, ' ');
	free(node->content);
	free(node);
	ret = validate_set(content);
	printf("ret: %s\n", ret);
	if (ret != NULL)
	{
		if (args->size > 1)
		{
			if (args->head)
			{
				to_free = args->head->content;
				args->head->content = ret;
				free(to_free);
			}
		}
		ft_free_str_vector(content);
		return (1);
	}
	set_var(sc, content);
	ft_free_str_vector(content);
	return (0);
}
