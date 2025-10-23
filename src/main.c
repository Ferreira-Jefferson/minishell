#include "../../includes/minishell.h"

struct env {
	char *key;
	char *value;
} ;

struct group
{
	t_hash_table	*table;
	char *input;
};

int ex_get_value_variable(char **new_str, char *str)
{
	size_t i;
	char tmp;
	char *var;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		i++;
	tmp = str[i];
	str[i] = '\0';
	var = str_new(str);
	str[i] = tmp;
	*new_str = str_cat(*new_str, "XXX");
	return (i);
}

int ex_question_mark(char **new_str)
{
	*new_str = str_cat(*new_str, "127");
	return (1);
}

int ex_double_dollar(char **new_str)
{
	*new_str = str_cat(*new_str, "12345");
	return (1);
}

void expander(struct group *values)
{
	char *new_str = str_new("");
	char str_tmp[2];
	
	while (*values->input)
	{
		if (*values->input == '$')
		{
			values->input++;
			if (*values->input == '$')
				values->input += ex_double_dollar(&new_str);
			else if (*values->input == '?')
				values->input += ex_question_mark(&new_str);
			else if (ft_isalpha(*values->input))
				values->input += ex_get_value_variable(&new_str, values->input);
			continue;
		}
		str_tmp[0] = *values->input;
		str_tmp[1] = '\0';
		new_str = str_cat(new_str, str_tmp);
		values->input++;
	}
	printf("fim: %s\n", new_str);
}

int	main(int argc, char *argv[], char **envp)
{
	t_hash_table	*table;
	char			*input;

	(void)argc;
	(void)argv;
	table = env_load(envp);
	struct group values;
	
	values.table = table;
	while (1)
	{
		input = readline("minishell~$ ");
		if (!input && get_g_signal_status() == 0)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		values.input = str_new(input);
		expander(&values);
		free(input);
		str_free(values.input);
	}
	ht_free(table);
	return (0);
}