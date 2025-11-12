#include "built_in.h"

int	b_unset(t_shell_context *sc, t_dlist	*args)
{
	t_dnode	*node;

	node = malloc(sizeof(t_dnode));
	if (!args)
		return (1);
	ft_dlstremove_at(args, 0, free);
	if (args->size == 0)
		return (0);
	while (args->head)
	{
		node->content = str_new(args->head->content);
		if (expander(sc, node))
			return (1);
		ht_delete(sc->env, node->content);
		args->head = args->head->next;
	}
	return (0);
}
