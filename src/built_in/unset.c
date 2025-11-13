#include "built_in.h"

int	b_unset(t_shell_context *sc, t_dlist	*args)
{
	t_dnode	*node;
	char	*to_free;

	if (!args || args->size == 0)
		return (0);
	ft_dlstremove_at(args, 0, free);
	if (args->size == 0)
		return (0);
	node = malloc(sizeof(t_dnode));
	if (!args)
		return (1);
	node->content = str_new("");
	while (args->head && args->head->content)
	{
		node->content = str_replace(node->content, args->head->content);
		to_free = node->content;
		expander(sc, node);
		str_free(to_free);
		ht_delete(sc->env, node->content);
		args->head = args->head->next;
	}
	free(node->content);
	free(node);
	return (0);
}
