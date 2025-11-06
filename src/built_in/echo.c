#include "built_in.h"

int	is_valid_flag(t_shell_context *sc, char *flag)
{
	t_dnode	*node;
	char	*content;
	int		is_valid;

	if (*flag != '-')
		return (0);
	if (ft_strlen(flag) == 1)
		return (0);
	node = ft_dlstnew(flag);
	if (!node)
		return (0);
	expander(sc, node);
	content = (char *)node->content;
	content++;
	is_valid = 1;
	while (*content && is_valid)
	{
		if (*content != 'n')
			is_valid = 0;
		content++;
	}
	free(node->content);
	free(node);
	return (is_valid);
}

void	b_echo(t_shell_context *sc, t_dlist	*args)
{
	int		valid_flag;
	t_dnode	*node;

	(void) sc;
	node = malloc(sizeof(t_dnode));
	if (!args)
		return ;
	valid_flag = is_valid_flag(sc, args->head->content);
	if (valid_flag)
		args->head = args->head->next;
	while (args->head)
	{
		node->content = str_new(args->head->content);
		expander(sc, node);
		printf("%s", (char *) node->content);
		if (args->head->next)
			printf(" ");
		args->head = args->head->next;
	}
	if (!valid_flag)
		printf("\n");
}
