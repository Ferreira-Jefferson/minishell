/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:49:16 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/11 09:00:01 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	print_error(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putchar_fd(':', fd);
	ft_putchar_fd(' ',fd);
	ft_putendl_fd(s2, fd);
	return (1);
}
