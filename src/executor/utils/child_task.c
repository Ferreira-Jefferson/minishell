/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:10:36 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 15:10:52 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	child_task(char *path, char **argv, char **envp)
{
	if (!path)
	{
		print_error(argv[0], "command not found", 2);
		free_arr(envp);
		exit (127);
	}
	execve(path, argv, envp);
	perror(argv[0]);
	free(path);
	free_arr(envp);
	if (errno == EACCES)
		exit(126);
	exit(127);
}
