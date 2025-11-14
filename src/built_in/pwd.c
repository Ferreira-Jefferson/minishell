/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:05:15 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 09:08:25 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	b_pwd(t_shell_context *sc, t_dlist	*args)
{
	(void) args;
	if (!sc || !args)
		return (1);
	if (!sc->pwd)
		return (1);
	printf("%s\n", sc->pwd);
	return (0);
}
