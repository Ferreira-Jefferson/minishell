/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_heredoc_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:35:16 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/12 17:36:29 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	del_heredoc_files(void *data)
{
	char	*filename;

	filename = (char *)data;
	if (!filename)
		return ;
	unlink(filename);
	free(filename);
}
