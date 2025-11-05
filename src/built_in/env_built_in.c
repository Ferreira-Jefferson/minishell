#include "built_in.h"

static void	print_env(t_env_item *env_item, char **str_env)
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

char	*b_env(t_shell_context *sc)
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
			if (env_item->type == ENV || \
				(env_item->type == EXPORT && env_item->value != NULL))
				print_env(env_item, &str_env);
		}
		i++;
	}
	return (str_env);
}
