#include "minishell.h"

t_hash_table	*env_load(char **envp)
{
	t_hash_table	*table;
	char			*key;
	char			*value;
	char			*first_equal;

	table = ht_create();
	if (!table)
		return (NULL);
	while (*envp)
	{
		first_equal = ft_strchr(*envp, '=');
		if (first_equal)
		{
			key = malloc(first_equal - *envp + 1);
			if (!key)
				return (NULL);
			ft_strlcpy(key, *envp, first_equal - *envp + 1);
			value = ft_strdup(first_equal + 1);
			ht_insert(table, key, value, (t_env_type) ENV);
			free(key);
			free(value);
		}
		envp++;
	}
	return (table);
}

char	*ft_str_toupper(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

void	ft_free_str_vector(char **str_vector)
{
	char	**aux;

	aux = str_vector;
	while (*aux)
	{
		free(*aux);
		aux++;
	}
	free(str_vector);
}


t_shell_context	*ft_setup_sc(char **envp)
{
	t_shell_context	*sc;

	sc = (t_shell_context *) malloc(sizeof(t_shell_context));

	sc->pid_ms = getpid();
	//sc->ast_root = create_complex_test_ast();
	sc->last_status = 0;
	sc->env = env_load(envp);
	sc->env_copy = env_load(envp);

	return (sc);
}

void	free_sc(t_shell_context	*sc)
{
	ht_free(sc->env);
	ht_free(sc->env_copy);
	free(sc);
}