/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 16:10:22 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	sc = ft_setup_sc(envp);
	setup_signals();
	rl_event_hook = ft_event_hook;
	while (1)
	{
		ft_define_rl_prompt(sc);
		input = readline(sc->rl_prompt);
		if (!input && get_g_signal_status() == 0)
		{
			free(input);
			b_exit(sc, NULL);
			return (0);
		}
		if (input && input[0] != '\0')
			add_history(input);
		free(input);
	}
	return (0);
}
