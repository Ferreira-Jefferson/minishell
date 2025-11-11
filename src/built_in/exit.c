#include "built_in.h"

int ft_print_error(char *content,  char *message, int status)
{
	char *output;

	output = str_new("bash: ");
	output = str_cat(output, "exit: ");
	output = str_cat(output, content);
	output = str_cat(output, " ");
	output = str_cat(output, message);
	perror(output);
	str_free(output);
	return (status);
}

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
		if (!ft_is_numeric(split[0]))
			status = ft_print_error(node->content, "numeric argument required", 2);
		else if (split[1])
			status = ft_print_error(node->content, "too many arguments", 1);
		else
			status = ft_atoi(split[0]) % 256;
	}
	str_free(to_free);
	ft_free_str_vector(split);
	ft_dlstdelone(node, free);
	return (status);	
}

void	b_exit(t_shell_context *sc, t_dlist	*args)
{
	int	status;

	if (!args || args->size == 0)
		status = sc->last_status;
	else
		status = ft_validate(sc, args);
	free_sc(sc);
	printf("exit\n");
	exit(status);
}
