/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:49:16 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/14 16:06:09 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	print_error(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putchar_fd(':', fd);
	ft_putchar_fd(' ', fd);
	ft_putendl_fd(s2, fd);
	return (1);
}

int	print_here_error(char *s1, int fd)
{
	ft_putstr_fd("minishell: warning: here-document at \
line 2 delimited by end-of-file (wanted `", fd);
	ft_putstr_fd(s1, fd);
	ft_putendl_fd("')", fd);
	return (1);
}
