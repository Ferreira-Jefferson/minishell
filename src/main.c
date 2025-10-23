/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:37:47 by joaolive          #+#    #+#             */
/*   Updated: 2025/10/23 09:21:13 by joaolive         ###   ########.fr       */
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
		// função que vai tratar o input
		free(input);
	}
	ht_free(table);
	return (0);
}
