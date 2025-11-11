/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:12:27 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 15:13:01 by joaolive         ###   ########.fr       */
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
