#include "built_in.h"

int	ft_validate(t_shell_context *sc, t_dlist *args)
{
	t_dnode	*node;
	int		status;
	char	*to_free;
	char	**split;

	node = ft_dlstnew("");
	node->content = ft_create_content(args);
	to_free = node->content;
	expander(sc, node);
	split = ft_split(node->content, ' ');
	if (!split)
		status = sc->last_status;
	else
	{
		if (split[0] && !ft_is_numeric(split[0]))
			status = ft_print_error("exit:", split[0], "numeric argument required", 2);
		else if (split[1])
			status = ft_print_error("exit:", "", "too many arguments", 1);
		else
			status = ft_atoi(split[0]) % 256;
	}
	str_free(to_free);
	ft_free_str_vector(split);
	ft_dlstdelone(node, free);
	return (status);	
}

int	b_exit(t_shell_context *sc, t_dlist	*args)
{
	int	status;

	if (!args)
		return (1);
	ft_dlstremove_at(args, 0, free);
	if (args->size == 0)
		status = sc->last_status;
	else
		status = ft_validate(sc, args);
	free_sc(sc);
	printf("exit\n");
	exit(status);
	return (1);
}
