#include "expander.h"

int	ex_handle_tilde(t_shell_context *sc, char *content, \
	int index, char **new_str)
{
	int		len;
	int		is_valid;
	char	*key;

	
	len = 0;
	is_valid = ((content && content[index + 1] == '\0') || (content && content[index + 1] != '\0' \
	&& (ft_isspace(content[index + 2]) || content[index + 2] == '/')));
	if (is_valid && content[index + 1] == '+')
	{
		key = ex_get_key(str_new("PWD"));
		len = 2;
	}
	else if (is_valid && content[index + 1] == '-')
	{
		key = ex_get_key(str_new("OLDPWD"));
		len = 2;
	}
	else if (content[index + 1] == '\0' || ft_isspace(content[index + 1]))
	{
		key = ex_get_key(str_new("HOME"));
		len = 1;
	}
	if (len)
		ex_get_value_variable(sc, new_str, key);
	return (len);
}


void	expander(t_shell_context *sc, t_dnode *node)
{
	char	*new_str;
	char	*content;
	int		start_quotes;

	new_str = str_new("");
	content = (char *) node->content;
	start_quotes = ex_quotes(&content);
	ex_scape(sc, content, &new_str, start_quotes);
	content = str_new(new_str);
	new_str = str_replace(new_str, "");
	ex_tildle(sc, content, &new_str, start_quotes);
	content = str_new(new_str);
	new_str = str_replace(new_str, "");
	ex_vars(sc, content, &new_str, start_quotes);
	node->content = str_replace(node->content, new_str);
	str_free(new_str);
	str_free(content);
}
