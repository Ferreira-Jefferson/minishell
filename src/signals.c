/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:02:48 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 16:02:49 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal_status;

int	get_g_signal_status(void)
{
	return (g_signal_status);
}

void	reset_g_signal_status(void)
{
	g_signal_status = 0;
}

void	handler(int signum)
{
	g_signal_status = signum;
}

int	setup_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (0);
}
