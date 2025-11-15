/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 16:29:06 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_data(t_shell_context *sc)
{
	if (sc->input)
	{
		free(sc->input);
		sc->input = NULL;
	}
	ft_dlstclear(sc->heredoc_files, del_heredoc_files);
	ft_dlstdestroy(&sc->tokens, free_token);
	sc->tokens = NULL;
	free_node(sc->ast_root);
	sc->ast_root = NULL;
}

int	ft_event_hook(void)
{
	if (get_g_signal_status() != 0)
		rl_done = 1;
	return (0);
}

void	ft_core(t_shell_context *sc)
{
	if (sc->input[0] != '\0')
		add_history(sc->input);
	sc->tokens = tokenize(sc->input, 0);
	sc->ast_root = parse_cmd_list(sc->tokens);
	if (!traveler_handler(sc->ast_root, sc))
		executor(sc);
	free_command_data(sc);
}

int	ft_handle_argv_input(t_shell_context *sc, int argc, char *argv[])
{
	if (argc == 1)
		return (0);
	sc->input = ft_strdup(argv[1]);
	if (ft_strcmp(argv[1], "-c") == 0)
	{
		if (argc == 2)
		{
			ft_print_error(sc, argv[1], "option requires an argument", 2);
			return (1);
		}
		sc->input = ft_strdup(argv[2]);
	}
	ft_core(sc);
	return (1);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell_context	*sc;

	sc = ft_setup_sc(envp);
	setup_signals();
	rl_event_hook = ft_event_hook;
	if (ft_handle_argv_input(sc, argc, argv))
		return (sc->last_status);
	while (1)
	{
		ft_define_rl_prompt(sc);
		sc->input = readline(sc->rl_prompt);
		if (get_g_signal_status() != 0)
			reset_g_signal_status();
		if (!sc->input)
			b_exit(sc, NULL, 1);
		else
			ft_core(sc);
	}
	return (sc->last_status);
}
