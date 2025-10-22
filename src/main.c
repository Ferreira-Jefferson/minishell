/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/22 12:16:35 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void expander(struct group *values)
{
	char *new_str = str_new("");
	(void) new_str;
	char *dollar_sign;
	char *space_or_end;
	char *str_to_spander;
	// char len_var;
	
	dollar_sign = ft_strchr(values->input, '$');
	if (dollar_sign)
	{
		space_or_end = ft_strchr(dollar_sign, ' ');
		if (space_or_end)
			dollar_sign[space_or_end - dollar_sign] = '\0';
		str_to_spander = str_new(dollar_sign);
		values->input[dollar_sign - values->input] = '\0';
		new_str = str_cat(new_str, values->input);
		printf("[%s]: [%s]\n", str_to_spander, new_str);
		
	}
	
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
	}
	ht_free(table);
	return (0);
}