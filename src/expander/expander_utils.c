#include "expander.h"

char	*ex_get_key(char *str)
{
	size_t	i;
	char	*str_temp;

	str_temp = str_new(str);
	i = 0;
	while (str_temp[i] && !ft_isspace(str_temp[i]) && str_temp[i] != '*')
		i++;
	str_temp[i] = '\0';
	str = str_replace(str, str_temp);
	str_free(str_temp);
	return (str);
}

int	ex_get_value_variable(t_shell_context *sc, char **new_str, char *key)
{
	char	*value;
	int		len;

	value = ht_search(sc->env, key);
	if (!value)
	{
		len = str_len(key);
		str_free(key);
		return (len);
	}
	*new_str = str_cat(*new_str, value);
	str_free(value);
	len = str_len(key);
	str_free(key);
	return (len);
}

int	ex_question_mark(t_shell_context *sc, char **new_str)
{
	char	*question_mark;

	question_mark = ft_itoa(sc->last_status);
	*new_str = str_cat(*new_str, question_mark);
	free(question_mark);
	return (1);
}

int	ex_double_dollar(t_shell_context *sc, char **new_str)
{
	char	*double_dollar;

	double_dollar = ft_itoa(sc->pid_ms);
	*new_str = str_cat(*new_str, double_dollar);
	free(double_dollar);
	return (1);
}
