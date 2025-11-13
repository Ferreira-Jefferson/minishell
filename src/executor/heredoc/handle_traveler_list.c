/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:51:22 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/12 15:08:54 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_traveler_list(t_node *node, t_shell_context *context)
{
	t_bin_node	*list_node;
	int			status;

	list_node = (t_bin_node *)node;
	status = traveler_handler(list_node->left, context);
	if (status)
		return (status);
	return (traveler_handler(list_node->right, context));
}
