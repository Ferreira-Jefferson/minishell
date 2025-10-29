#include "expander.h"

static int	ex_handle_tilde(t_shell_context *sc, char *content, \
	int index, char **new_str)
{
	int		len;
	int		is_valid;
	char	*key;

	len = 0;
	is_valid = (content && content[index + 1] != '\0' \
	&& (ft_isspace(content[index + 2]) || content[index + 2] == '/'));
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
	else if (content[index + 1] && ft_isspace(content[index + 1]))
	{
		key = ex_get_key(str_new("HOME"));
		len = 1;
	}
	if (len)
		ex_get_value_variable(sc, new_str, key);
	return (len);
}

static int	ex_handler_vars(t_shell_context *sc, char *content, \
	int index, char **new_str)
{
	int	len;

	index++;
	len = 1;
	if (content[index] == '$')
		len += ex_double_dollar(sc, new_str);
	else if (content[index] == '?')
		len += ex_question_mark(sc, new_str);
	else if (ft_isalnum(content[index]))
		len += ex_get_value_variable(sc, new_str, \
			ex_get_key(str_new(&content[index])));
	return (len);
}

static void	ex_vars(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	char	len;
	size_t	index;

	index = 0;
	while (content[index])
	{
		len = 0;
		if (!start_quotes && content[index] == '~' && (index > 0 \
			&& ft_isspace(content[index - 1])))
			len = ex_handle_tilde(sc, content, index, new_str);
		else if (start_quotes != 1 && content[index] == '$' \
			&& content[index + 1] != '\0' \
			&& (!ft_isspace(content[index + 1]) \
			&& content[index + 1] != '~'))
			len = ex_handler_vars(sc, content, index, new_str);
		index += len;
		if (len)
			continue ;
		str_tmp[0] = content[index];
		str_tmp[1] = '\0';
		*new_str = str_cat(*new_str, str_tmp);
		index++;
	}
}

int	ex_handle_quotes(char **content)
{
	int		start_quotes;

	start_quotes = 0;
	if (*content && *(content)[0] == '\'')
		start_quotes = 1;
	else if (*content && *(content)[0] == '"')
		start_quotes = 2;
	if (start_quotes)
	{
		(*content)[str_len(*content) - 1] = '\0';
		(*content)++;
	}
	return (start_quotes);
}

void	expander(t_shell_context *sc, t_dnode *node)
{
	char	*new_str;
	char	*content;
	int		start_quotes;

	new_str = str_new("");
	content = (char *) node->content;
	start_quotes = ex_handle_quotes(&content);
	ex_vars(sc, content, &new_str, start_quotes);
	node->content = str_replace(node->content, new_str);
	str_free(new_str);
}
