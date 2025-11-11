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

int	b_export(t_shell_context *sc, t_dlist *args)
{
	t_hash_table	*table;
	t_env_item		*env_item;
	char			*str_env;
	int				i;
	char			*sorted;

	(void) args;
	i = 0;
	str_env = str_new("");
	table = sc->env;
	if (!table)
		return (1);
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			create_export_list(env_item, &str_env);
		}
		i++;
	}
	sorted = sort_export(str_env, 0, 0);
	printf("%s\n", sorted);
	str_free(sorted);
	return (0);
}
