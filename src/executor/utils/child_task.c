/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:10:36 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/14 13:47:32 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	child_task(char *path, char **argv, char **envp, t_shell_context *sc)
{
	sc->last_status = 127;
	if (!path)
	{
		print_error(argv[0], "command not found", 2);
		free_arr(envp);
		free(argv);
		b_exit(sc, NULL, 0);
	}
	execve(path, argv, envp);
	perror(argv[0]);
	free(path);
	free(argv);
	free_arr(envp);
	if (errno == EACCES)
		sc->last_status = 126;;
	b_exit(sc, NULL, 0);
}
