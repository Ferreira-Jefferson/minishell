/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:29:22 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/02 11:00:41 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_exec_list(t_node *node, t_shell_context *context)
{
	t_bin_node	*list_node;
	int			status;

	list_node = (t_bin_node *)node;
	execute_node(list_node->left, context);
	status = execute_node(list_node->right, context);
	return (status);
}
