#include "built_in.h"

static void	create_export_list(t_env_item *env_item, char **str_env)
{
	while (env_item)
	{
		if (str_len(*str_env) > 0 && (env_item + 1))
			*str_env = str_cat(*str_env, "\n");
		*str_env = str_cat(*str_env, "declare -x ");
		*str_env = str_cat(*str_env, env_item->key);
		if (env_item->value != NULL)
		{
			*str_env = str_cat(*str_env, "=");
			*str_env = str_cat(*str_env, "\"");
			*str_env = str_cat(*str_env, env_item->value);
			*str_env = str_cat(*str_env, "\"");
		}
		env_item = env_item->next;
	}
	free(env_item);
}

int	ft_isvalid_key(char *key)
{
	if (ft_strcmp(key, "_") == 0)
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void	set_export(t_shell_context *sc, t_dnode *node)
{
	char	*content;
	char	**split;

	content = node->content;
	split = ft_split(content, '=');
	if (!split)
		return ;
	if (!ft_isvalid_key(split[0]))
	{
		if (split[0][0] == '#')
			return (b_export(sc));
		printf("bash: export: '%s': not a valid identifier\n", split[0]);
	}
	if (ft_strchr(content, '='))
	{
		if (split[1] == NULL)
			return (ht_insert(sc->env, split[0], "", (t_env_type)EXPORT));
		ht_insert(sc->env, split[0], split[1], (t_env_type)EXPORT);
	}
	else
		ht_insert(sc->env, split[0], NULL, (t_env_type)EXPORT);
}

void	b_export(t_shell_context *sc)
{
	t_hash_table	*table;
	t_env_item		*env_item;
	char			*str_env;
	int				i;

	i = 0;
	str_env = str_new("");
	table = sc->env;
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			create_export_list(env_item, &str_env);
		}
		i++;
	}
	printf("%s\n", sort_export(str_env, 0, 0));
}
