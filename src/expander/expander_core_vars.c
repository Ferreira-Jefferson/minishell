#include "expander.h"


static int	ex_handler_vars(t_shell_context *sc, char *content, \
	int index, char **new_str)
{
	int	len;

	index++;
	len = 1;
	if (content[index] == '*')
		len += 1;
	if (content[index] == '$')
		len += ex_double_dollar(sc, new_str);
	else if (content[index] == '?')
		len += ex_question_mark(sc, new_str);
	else if (ft_isalnum(content[index]))
		len += ex_get_value_variable(sc, new_str, \
			ex_get_key(str_new(&content[index])));
	return (len);
}

static void	ex_set_new_str(char c, char **new_str)
{
	char	str_tmp[2];

	str_tmp[0] = c;
	str_tmp[1] = '\0';
	*new_str = str_cat(*new_str, str_tmp);
}

void	ex_vars(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	len;
	size_t	index;
	int		only_copy;

	only_copy = 0;
	index = 0;
	while (content[index])
	{
		len = 0;
		if (content[index] == '\'' && only_copy)
			only_copy = 0;
		else if (index > 0 && content[index] == '$' \
			&& content[index - 1] == '\'')
			only_copy = 1;
		else if (start_quotes != 1 && content[index] == '$' \
			&& content[index + 1] != '\0' \
			&& !ft_isspace(content[index + 1]) \
			&& content[index + 1] != '~')
			len = ex_handler_vars(sc, content, index, new_str);
		index += len;
		if (len)
			continue ;
		ex_set_new_str(content[index], new_str);
		index++;
	}
}
