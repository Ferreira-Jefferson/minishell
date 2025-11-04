#include "built_in.h"

static void set_env(t_env_item *env_item, char **str_env)
{
	while (env_item)
	{
		if (str_len(*str_env) > 0 && (env_item + 1))
			*str_env = str_cat(*str_env, "\n");
		*str_env = str_cat(*str_env, env_item->key);
		*str_env = str_cat(*str_env, "=");
		*str_env = str_cat(*str_env, env_item->value);
		env_item = env_item->next;
	}
	free(env_item);
}

char *b_env(t_shell_context *sc)
{
	t_hash_table *table;
	t_env_item	*env_item;
	char		*str_env;
	int			i;

	i = 0;
	str_env = str_new("");
	table = sc->env_global;
	while (i < table->size)
	{
		if (table->items[i])
		{
			env_item = table->items[i];
			set_env(env_item, &str_env);
		}
		i++;
	}
	return (str_env);
}
