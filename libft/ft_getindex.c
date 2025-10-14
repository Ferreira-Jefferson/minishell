/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 08:00:22 by jtertuli          #+#    #+#             */
/*   Updated: 2025/08/10 08:11:33 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getindex(const char *str, unsigned char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}
