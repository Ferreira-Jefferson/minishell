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
			ht_insert(table, key, value);
			free(key);
			free(value);
		}
		envp++;
	}
	return (table);
}

char	*ft_str_toupper(char *str)
{
	char	*aux;
	int		i;

	i = 0;
	aux = str_new(str);
	while (aux[i])
	{
		aux[i] = ft_toupper(aux[i]);
		i++;
	}
	return (aux);
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
