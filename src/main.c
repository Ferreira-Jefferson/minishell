/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 15:51:44 by jtertuli         ###   ########.fr       */
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
	// t_dnode *node = ft_dlstnew("$USER-\'$USER\'-\"$USER\"");

	sc = ft_setup_sc(envp);

//	ht_print(sc->env);
	t_dnode *node_1 = ft_dlstnew("~/42sp");
	ft_dlstinsert_node_at(args, node_1, 0);

	printf("pwd (antes): [%s]\n", sc->pwd);
	b_cd(sc, args);
	printf("pwd (depois): [%s]\n", sc->pwd);
	// ht_print(sc->env);

	// t_dnode *node_2 = ft_dlstnew("\\\"");
	// ft_dlstinsert_node_at(args, node_2, 1);

	// t_dnode *node_3 = ft_dlstnew("\\\\");
    // ft_dlstinsert_node_at(args, node_3, 2);

    // t_dnode *node_4 = ft_dlstnew("\\n");
    // ft_dlstinsert_node_at(args, node_4, 3);

    // t_dnode *node_5 = ft_dlstnew("teste\"\"teste");
    // ft_dlstinsert_node_at(args, node_5, 4);

    // t_dnode *node_6 = ft_dlstnew("~");
    // ft_dlstinsert_node_at(args, node_6, 5);

    // t_dnode *node_7 = ft_dlstnew("~$HOME");
    // ft_dlstinsert_node_at(args, node_7, 6);

    // t_dnode *node_8 = ft_dlstnew("$~");
    // ft_dlstinsert_node_at(args, node_8, 7);

    // t_dnode *node_9 = ft_dlstnew("~$");
    // ft_dlstinsert_node_at(args, node_9, 8);

    // t_dnode *node_10 = ft_dlstnew("~+N");
    // ft_dlstinsert_node_at(args, node_10, 9);

    // t_dnode *node_11 = ft_dlstnew("~-N");
    // ft_dlstinsert_node_at(args, node_11, 10);

    // t_dnode *node_12 = ft_dlstnew("A~");
    // ft_dlstinsert_node_at(args, node_12, 11);

    // t_dnode *node_13 = ft_dlstnew("~A");
    // ft_dlstinsert_node_at(args, node_13, 12);

    // t_dnode *node_14 = ft_dlstnew("A~A");
    // ft_dlstinsert_node_at(args, node_14, 13);

    // t_dnode *node_15 = ft_dlstnew("~+/foo");
    // ft_dlstinsert_node_at(args, node_15, 14);

    // t_dnode *node_16 = ft_dlstnew("~-/bar");
    // ft_dlstinsert_node_at(args, node_16, 15);

    // t_dnode *node_17 = ft_dlstnew("$$");
    // ft_dlstinsert_node_at(args, node_17, 16);

    // t_dnode *node_18 = ft_dlstnew("$?");
    // ft_dlstinsert_node_at(args, node_18, 17);

    // t_dnode *node_19 = ft_dlstnew("$VA");
    // ft_dlstinsert_node_at(args, node_19, 18);

    // t_dnode *node_20 = ft_dlstnew("$USR\"\"oi\"\"\"");
    // ft_dlstinsert_node_at(args, node_20, 19);

	// b_set_export(sc, args);
	// b_export(sc);
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

	// free(node->content);
	// free(node_2->content);
	// free(node);
	// free(node_2);
	// ft_dlstdestroy(&args, NULL);

	// free_sc(sc);
	
	// printf("\n");

	//return (0);

	setup_signals();
	t_dnode *node = ft_dlstnew("");
	rl_event_hook = ft_event_hook;
	while (1)
	{
		ft_define_rl_prompt(sc);
		input = readline(sc->rl_prompt);
		if (!input && get_g_signal_status() == 0)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input && input[0] != '\0') // Verifica se input não é NULL
			add_history(input);
		node->content = str_new(input);
		if (expander(sc, node))
		{
			free(input);
			return (1);
		}
		printf("main: [%s]\n", (char *) node->content);
		free(input);
	}
	// ht_free(table);
	free_sc(sc);
	return (0);
}

