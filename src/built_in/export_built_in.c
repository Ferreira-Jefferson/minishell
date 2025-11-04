#include "built_in.h"

static void print_export(t_env_item *env_item, char **str_env)
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

void	set_export(t_shell_context *sc, t_dnode *node)
{
	char *content;
	char **split;

	content = node->content;
	split = ft_split(content, '=');
	if (!split)
		return ;
	if (ft_strchr(content, '='))
	{
		if (split[1] == NULL)
			ht_insert(sc->env, split[0], "", (t_env_type)EXPORT);
		else
			ht_insert(sc->env, split[0], split[1], (t_env_type)EXPORT);
	}
	else
		ht_insert(sc->env, split[0], NULL, (t_env_type)EXPORT);
}

char	*b_export(t_shell_context *sc)
{
	t_hash_table *table;
	t_env_item	*env_item;
	char		*str_env;
	int			i;

	i = 0;
	str_env = str_new("");
	table = sc->env;
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			print_export(env_item, &str_env);
		}
		i++;
	}
	return (sort_export(str_env, 0, 0));
}