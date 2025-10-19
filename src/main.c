/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/19 14:49:54 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **envp)
{
	t_hash_table	*table;
	char			*input;
	
	(void)argc;
	(void)argv;	
	table = env_load(envp);
	ht_print(table);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		// função que vai tratar o input
		free(input);
	}
	ht_free(table);
	return (0);
}
