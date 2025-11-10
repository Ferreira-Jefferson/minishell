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
	return (is_valid);
}

static char	*create_content(t_dlist	*args)
{
	char	*content;

	content = str_new("");
	while (args && args->head)
	{
		printf("cat antes: %p\n", content);
		content = str_cat(str_clear(content), args->head->content);
		printf("cat depois: %p\n", content);
		if (args->head->next)
			content = str_cat(str_clear(content), " ");
		args->head = args->head->next;
	}
	return (content);
}

void	b_echo(t_shell_context *sc, t_dlist	*args)
{
	int		valid_flag;
	t_dnode	*node;
	char	*tmp;

	(void) sc;
	if (!args)
		return ;
	valid_flag = is_valid_flag(sc, args->head->content);
	if (valid_flag)
		free(ft_dlstpop_front(args));
	tmp = create_content(args);
	node = ft_dlstnew(tmp);
	printf("%s\n", (char *) node->content);
	expander(sc, node);
	printf("%s", (char *) node->content);
	//printf("teste: %zu\n\n", str_len(tmp));
	if (!valid_flag)
		printf("\n");
	str_free(tmp);
	ft_dlstdelone(node, free);
}
