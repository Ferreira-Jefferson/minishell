#include "expander.h"

int	ex_quotes(char **content)
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

void	ex_tildle(t_shell_context *sc, char *content, \
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
		index += len;
		if (len)
			continue ;
		str_tmp[0] = content[index];
		str_tmp[1] = '\0';
		*new_str = str_cat(*new_str, str_tmp);
		index++;
	}
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

void	ex_vars(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	char	len;
	size_t	index;

	index = 0;
	while (content[index])
	{
		len = 0;
		if (start_quotes != 1 && content[index] == '$' \
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

void	ex_scape(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	size_t	index;
	(void) sc;

	index = 0;
	while (content[index])
	{
		if (start_quotes != 1 \
			&& content[index] == '\\' \
			&& content[index + 1])
				index++;
		str_tmp[0] = content[index];
		str_tmp[1] = '\0';
		*new_str = str_cat(*new_str, str_tmp);
		index++;
	}
}

//echo \' \" \\ \n teste ~ ~$HOME $~ ~$ ~+N ~-N A~ ~A A~A ~+/foo ~-/bar $$ $? $VA $USR

// ' " \ n teste /nfs/homes/jtertuli ~/nfs/homes/jtertuli $~ ~$ ~+N ~-N A~ ~A A~A /nfs/homes/jtertuli/42sp/personal/minishell/foo /nfs/homes/jtertuli/42sp/personal/minishell/bar 333295 0

// ' " \ n teste /nfs/homes/jtertuli ~/nfs/homes/jtertuli $~ ~$ ~+N ~-N A~ ~A A~A /nfs/homes/jtertuli/42sp/personal/minishell/foo /nfs/homes/jtertuli/42sp/personal/minishell/bar 332250 0  