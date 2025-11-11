/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_and.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:56:42 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/02 11:03:06 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_exec_and(t_node *node, t_shell_context *context)
{
	t_bin_node	*and_node;
	int			status;

	and_node = (t_bin_node *)node;
	status = execute_node(and_node->left, context);
	if (!status)
		status = execute_node(and_node->right, context);
	return (status);
}
