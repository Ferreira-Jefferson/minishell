/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_and.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:02:59 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/12 15:08:51 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_traveler_and(t_node *node, t_shell_context *context)
{
	t_bin_node	*and_node;
	int			status;

	and_node = (t_bin_node *)node;
	status = traveler_handler(and_node->left, context);
	if (!status)
		status = traveler_handler(and_node->right, context);
	return (status);
}
