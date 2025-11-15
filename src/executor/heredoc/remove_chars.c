/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:56:55 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/14 15:34:33 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*remove_chars(char *str, char *set)
{
	char	*src;
	char	*dest;

	if (!str || !set)
		return (NULL);
	src = str;
	dest = str;
	while (*src)
	{
		if (!ft_strchr(set, *src))
			*dest++ = *src;
		src++;
	}
	*dest = '\0';
	return (str);
}
