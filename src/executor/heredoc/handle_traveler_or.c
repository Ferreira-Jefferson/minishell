/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_traveler_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:06:57 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/12 15:09:03 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	handle_traveler_or(t_node *node, t_shell_context *context)
{
	t_bin_node	*or_node;
	int			status;

	or_node = (t_bin_node *)node;
	status = traveler_handler(or_node->left, context);
	if (status)
		status = traveler_handler(or_node->right, context);
	return (status);
}
