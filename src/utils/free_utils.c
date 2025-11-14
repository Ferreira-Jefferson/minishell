/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:12:27 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/13 18:12:10 by jtertuli         ###   ########.fr       */
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
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}


int free_ret(t_dlist **list, void *arg, void (*del)(void *), int ret)
{
	if (list)
		ft_dlstdestroy(list, del);
	if (arg)
		free(arg);
	return (ret);
}

void	ft_del_fds(void *fd)
{
	int	*fd_value;

	fd_value = (int *)fd;
	close(*fd_value);
}

void	free_sc(t_shell_context	*sc)
{
	ht_free(sc->env);
	ht_free(sc->env_copy);
	str_free(sc->pwd);
	str_free(sc->rl_prompt);
	free_node(sc->ast_root);
	ft_dlstdestroy(&sc->fds, ft_del_fds);
	ft_dlstdestroy(&sc->heredoc_files, del_heredoc_files);
	free(sc);
}

