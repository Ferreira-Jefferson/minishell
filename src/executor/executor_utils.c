/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:47:28 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/13 11:27:51 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**copy_args(t_dlist *lst)
{
	char	**argv;
	t_dnode	*curr;
	int		i;

	if (!lst || !lst->size)
		return (NULL);
	argv = ft_calloc(lst->size + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	curr = lst->head;
	while (curr)
	{
		argv[i++] = (char *)curr->content;
		curr = curr->next;
	}
	return (argv);
}

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp((char *)cmd, "echo") || !ft_strcmp((char *)cmd, "cd")
		|| !ft_strcmp((char *)cmd, "pwd") || !ft_strcmp((char *)cmd, "export")
		|| !ft_strcmp((char *)cmd, "unset") || !ft_strcmp((char *)cmd, "env")
		|| !ft_strcmp((char *)cmd, "exit"))
		return (true);
	return (false);
}

int	reset_close_fd(int *std_bak, int val)
{
	dup2(std_bak[0], STDIN_FILENO);
	dup2(std_bak[1], STDOUT_FILENO);
	close(std_bak[0]);
	close(std_bak[1]);
	return (val);
}






