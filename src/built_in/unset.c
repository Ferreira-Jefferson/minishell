#include "built_in.h"

void	b_uset(t_shell_context *sc, t_dlist	*args)
{
	t_dnode	*node;

	node = malloc(sizeof(t_dnode));
	if (!args)
		return ;
	while (args->head)
	{
		node->content = str_new(args->head->content);
		expander(sc, node);
		ht_delete(sc->env, node->content);
		args->head = args->head->next;
	}
}
