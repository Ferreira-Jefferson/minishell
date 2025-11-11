/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 08:47:28 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 15:13:05 by joaolive         ###   ########.fr       */
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
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5))
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






