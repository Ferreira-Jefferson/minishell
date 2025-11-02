/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/01 17:40:39 by jtertuli         ###   ########.fr       */
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

t_shell_context	*ft_setup_sc(char **envp)
{
	t_shell_context	*sc;

	sc = (t_shell_context *) malloc(sizeof(t_shell_context));

	sc->pid_ms = getpid();
	//sc->ast_root = create_complex_test_ast();
	sc->last_status = 0;
	sc->env_local = NULL;
	sc->env_global = env_load(envp);
	sc->env_copy = env_load(envp);

	return (sc);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell_context	*sc;
	char	*input;

	t_dnode *node = malloc(sizeof(t_dnode));
	node->content = str_new("\\' \\\" \\\\ \\n teste ~ ~$HOME $~ ~$ ~+N ~-N A~ ~A A~A ~+/foo ~-/bar $$ $? $VA $USR");
	
	(void)argc;
	(void)argv;
	sc = ft_setup_sc(envp);
	printf("Antes:[%s]\n", (char *)node->content);
		expander(sc, node);
	printf("Depois:[%s]\n", (char *)node->content);
	setup_signals();
	rl_catch_signals = 0;
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

