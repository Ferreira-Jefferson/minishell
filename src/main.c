/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 10:00:55 by joaolive         ###   ########.fr       */
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

void	ft_core(t_shell_context	*sc)
{
	if (sc->input[0] != '\0')
		add_history(sc->input);
	sc->tokens = tokenize(sc->input, 0);
	sc->ast_root = parse_cmd_list(sc->tokens);
	if (!traveler_handler(sc->ast_root, sc))
		executor(sc);
	free_command_data(sc);
}

int	main(int argc, char *argv[], char **envp)
{
	t_shell_context	*sc;

	(void) argc;
	(void) argv;
	sc = ft_setup_sc(envp);
	setup_signals();
	rl_event_hook = ft_event_hook;
	while (1)
	{
		ft_define_rl_prompt(sc);
		sc->input = readline(sc->rl_prompt);
		if (get_g_signal_status() != 0)
			reset_g_signal_status();
		if (!sc->input)
		{
			b_exit(sc, NULL, 1);
			return (0);
		}
		else
			ft_core(sc);
	}
	return (0);
}
