/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:12:27 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/15 15:51:23 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_str(char *str, int val)
{
	free(str);
	return (val);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	free_ret(t_dlist **list, void *arg, void (*del)(void *), int ret)
{
	if (list)
		ft_dlstdestroy(list, del);
	if (arg)
		free(arg);
	return (ret);
}

void	close_fd(void *data)
{
	int	fd;

	fd = (int)(long)data;
	if (fd > 2)
		close(fd);
}

void	free_sc(t_shell_context	*sc)
{
	if (!sc)
		return ;
	free_command_data(sc);
	ht_free(sc->env);
	ht_free(sc->env_copy);
	str_free(sc->pwd);
	str_free(sc->cmd);
	str_free(sc->rl_prompt);
	ft_dlstdestroy(&sc->fds, close_fd);
	ft_dlstdestroy(&sc->heredoc_files, del_heredoc_files);
	free(sc);
}
