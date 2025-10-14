/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:09:42 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/02 08:24:57 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_only_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
