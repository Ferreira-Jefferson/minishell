/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:56:42 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/02 11:15:24 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_exec_or(t_node *node, t_shell_context *context)
{
	t_bin_node	*or_node;
	int			status;

	or_node = (t_bin_node *)node;
	status = execute_node(or_node->left, context);
	if (status)
		status = execute_node(or_node->right, context);
	return (status);
}
