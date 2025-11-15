/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:10:09 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 15:54:07 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	traveler_callback(void *data, void *context_data)
{
	t_node			*node;
	t_shell_context	*context;
	int				status;

	node = (t_node *)data;
	context = (t_shell_context *)context_data;
	status = traveler_handler(node, context);
	if (status)
		return (status);
	return (0);
}

int	handle_traveler_pipe(t_node *node, t_shell_context *context)
{
	t_pipe_node		*pipe_node;

	pipe_node = (t_pipe_node *)node;
	return (ft_dlstforeach_ctx(pipe_node->commands,
			traveler_callback, context));
}
