/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/30 08:12:43 by jtertuli         ###   ########.fr       */
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
	t_hash_table	*table;
	char			*input;

	(void)argc;
	(void)argv;
	setup_signals();
	rl_catch_signals = 0;
	rl_event_hook = ft_event_hook;
	table = env_load(envp);
	while (1)
	{
		input = readline("teste> ");
		if (!input && get_g_signal_status() == 0)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		if (ft_strcmp(input, "clear") == 0)
			clear_history();
		free(input);
	}
	ht_free(table);
	return (0);
}
