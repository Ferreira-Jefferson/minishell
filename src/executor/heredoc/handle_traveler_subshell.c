/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_subshell.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:23:28 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/12 15:28:21 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_traveler_subshell(t_node *node, t_shell_context *context)
{
	t_sub_node	*sub_node;
	int			status;

	sub_node = (t_sub_node *)node;
	status = traveler_handler(sub_node->sub_ast, context);
	return (status);
}
