/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 07:37:55 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/14 13:42:58 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_binary_len(unsigned int c)
{
	size_t	len;

	if (c == 0)
		return (1);
	len = 0;
	while (c)
	{
		c >>= 1;
		len++;
	}
	return (len);
}
