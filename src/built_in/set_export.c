#include "built_in.h"

static int	handle_set(t_shell_context *sc, t_dnode	*node, char **split)
{
	if (!split)
		return (-1);
	if (!ft_isvalid_key(split[0]))
	{
		if (split[0][0] != '#')
			printf("bash: export: '%s': not a valid identifier\n", split[0]);
		return (-1);
	}
	if (ft_strchr(node->content, '='))
	{
		if (split[1] == NULL)
			ht_update_insert(sc->env, split[0], "", (t_env_type) EXPORT);
		else
			ht_update_insert(sc->env, split[0], split[1], (t_env_type) EXPORT);
	}
	else
		ht_insert(sc->env, split[0], NULL, (t_env_type) EXPORT);
	return (0);
}

static void	set_var(t_shell_context *sc, t_dlist *args)
{
	t_dnode	*node;
	char	**split;
	int		ret_set;

	node = malloc(sizeof(t_dnode));
	if (!node)
		return ;
	while (args->head)
	{
		node->content = str_new(args->head->content);
		split = ft_split(node->content, '=');
		ret_set = handle_set(sc, node, split);
		str_free(node->content);
		ft_free_str_vector(split);
		if (ret_set == -1)
			return (free(node));
		args->head = args->head->next;
	}
	free(node);
}

int	b_set_export(t_shell_context *sc, t_dlist	*args)
{
	char	**split;

	if (!args || !args->head)
		return (1);
	split = ft_split(args->head->content, '=');
	if (!split)
		return (1);
	if (split[0][0] == '#')
	{
		ft_free_str_vector(split);
		return (b_export(sc));
	}
	ft_free_str_vector(split);
	set_var(sc, args);
	return (0);
}
