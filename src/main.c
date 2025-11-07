/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/07 11:58:51 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "ast.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * ==================================================================
 * FUNÇÃO DE HOOK
 * ==================================================================
 */

int	ft_event_hook(void)
{
	if (get_g_signal_status() != 0)
	{
		write(1, "^C", 2);
		rl_done = 1;
		reset_g_signal_status();
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell_context	*sc;
	char	*input;

	(void) argc;
	(void) argv;
	t_dlist	*args = ft_dlstinit();	
	t_dnode *node = malloc(sizeof(t_dnode));
	// node->content = str_new("\\' \\\" \\\\ \\n teste ~ ~$HOME $~ ~$ ~+N ~-N A~ ~A A~A ~+/foo ~-/bar $$ $? $VA $USR");

	sc = ft_setup_sc(envp);
	
	node->content = ft_strdup("ZDOTDIR1=1000");
	ft_dlstinsert_node_at(args, node, 0);

	t_dnode *node_2 = malloc(sizeof(t_dnode));
	node_2->content = ft_strdup("ZDOTDIR");
	ft_dlstinsert_node_at(args, node_2, 1);

	b_set_export(sc, args);
	b_export(sc);
	// printf("\n");
	// b_echo(sc, args);

	// printf("Antes:[%s]\n", (char *)node->content);
	// 	expander(sc, node);
	// printf("Depois:[%s]\n", (char *)node->content);
	
	// node->content = str_new("VAR=1000");
	// set_export(sc, node);
	// node->content = str_new("#a=");
	// set_export(sc, node);
	// node->content = str_new("a@=300");
	// set_export(sc, node);
	//b_export(sc);

	free(node->content);
	free(node_2->content);
	free(node);
	free(node_2);
	ft_dlstdestroy(&args, NULL);

	free_sc(sc);
	
	printf("\n");

	return (0);
	setup_signals();
	// rl_catch_signals = 0;
	rl_event_hook = ft_event_hook;
	while (1)
	{
		input = readline("teste> ");
		if (!input && get_g_signal_status() == 0)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input && input[0] != '\0') // Verifica se input não é NULL
			add_history(input);
		node->content = str_new(input);
		expander(sc, node);
		printf("main: [%s]\n", (char *) node->content);
		free(input);
	}
	// ht_free(table);
	return (0);
}

