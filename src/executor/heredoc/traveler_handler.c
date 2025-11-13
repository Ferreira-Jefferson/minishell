/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traveler_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:29:15 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/13 19:03:28 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	traveler_handler(t_node *node, t_shell_context *context)
{
	t_executor_func					handler;
	static const t_executor_func	traveler_table[] = {
		&handle_traveler_cmd,
		&handle_traveler_pipe,
		&handle_traveler_list,
		&handle_traveler_and,
		&handle_traveler_or,
		&handle_traveler_subshell
	};

	if (!node)
		return (1);
	handler = traveler_table[node->kind];
	return (handler(node, context));
}
