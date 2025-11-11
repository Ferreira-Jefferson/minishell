/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:04:38 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/10 18:11:40 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*match_path(char **path_dirs, char *cmd)
{
	char	*path;
	int		i;

	i = -1;
	while (path_dirs[++i])
	{
		path = ft_strjoinv(NULL, 3, path_dirs[i], "/", cmd);
		if (!path)
			return (NULL);
		if (access((const char *)path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*find_command_path(t_hash_table *env, char *cmd)
{
	char	*path_str;
	char	**path_dirs;
	char	*path;

	if (ft_strchr((const char *)cmd, '/'))
	{
		if (access((const char *)cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_str = ht_search(env, "PATH");
	if (!path_str)
		return (NULL);
	path_dirs = ft_split(path_str, ':');
	if (!path_dirs)
		return (NULL);
	path = match_path(path_dirs, cmd);
	free_arr(path_dirs);
	return (path);
}
