#include "built_in.h"

int	b_uset(t_shell_context *sc, t_dlist	*args)
{
	t_dnode	*node;

	node = malloc(sizeof(t_dnode));
	if (!args)
		return (1);
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
